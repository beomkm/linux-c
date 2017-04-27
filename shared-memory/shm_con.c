#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
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
    if((mysem = sem_open("mysem", 0, 0777, 0)) == SEM_FAILED) {
        perror("Sem Open Error");
        exit(1);
    }

    if((shmid = shmget((key_t)key, shsize, IPC_CREAT|0666))<0) {
        perror("shmget");
        exit(1);
    }

    if((shm = (char*)shmat(shmid, NULL, 0)) == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    for(;;) {
        if(sem_trywait(mysem) == 0) {
            for(int i=0; i<100; i++) {
                printf("%d", (shm[i]));
            }

            putchar('\n');
            sem_post(mysem);
        }
        else {
            switch(errno) {
                case EAGAIN:
                    printf("EAGAIN\n");
                    break;
                case EDEADLK:
                    printf("EDEADLK\n");
                    break;
                case EINTR:
                    printf("EINTR\n");
                    break;
            }
        }

        usleep(100*1000);
    }

    sem_close(mysem);
    shmdt(shm);

    return 0;
}
