//http://tibyte.kr/285

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>


int main(void)
{
    int shmid;
    size_t shsize = 1024;
    const int key = 16000;
    char *shm;

    sem_t *mysem;
    sem_unlink("mysem");
    if((mysem = sem_open("mysem", O_CREAT, 0777, 1)) == NULL) {
        perror("Sem Open Error");
        exit(1);
    }

    if((shmid = shmget((size_t)key, shsize, IPC_CREAT|0666))<0) {
        perror("shmget");
        exit(1);
    }

    if((shm = (char*)shmat(shmid, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    for(int i=0; i<100; i++) {
        shm[i] = 0;
    }


    for(;;) {
        sem_wait(mysem);
        for(int i=0; i<100; i++) {
            shm[i] = (shm[i]+1)%10;
        }
        usleep(1000*1000);
        sem_post(mysem);
        usleep(1000*1000);
    }

    getchar();

    sem_close(mysem);
    sem_unlink("mysem");

    shmdt(shm);
    shmctl(shmid, IPC_RMID, 0);

    return 0;
}
