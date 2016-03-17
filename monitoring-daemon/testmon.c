#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *t_function(void *arg);
int getObjPID(void);

int main(int argc, char* argv[])
{
	char input;
	char cmd[24];
	int objPID;

	//thread
	int res;
	pthread_t a_thread;

	
	res = pthread_create(&a_thread, NULL, t_function, NULL);
	if(res != 0) {
		perror("Thread creation failed");
		exit(1);
	}

	
	while(1) {
		
		scanf("%c", &input);
		objPID = getObjPID();
		switch(input) {
			case 'Q': //testmon 프로세스 종료
				printf("quit 'testmon'\n");
				exit(0);
				break;
			case 'K': //test프로세스 Kill
				if(objPID == -1) {
					printf("process 'test' isn't running.");
				}
				else {
					printf("kill 'test'\n");
					sprintf(cmd, "kill -9 %d", objPID);
					system(cmd);
				}
				break;
			case 'S': //test프로세스 Start 
				if(objPID == -1) {
					printf("start 'test'\n");
					if(argc == 2) sprintf(cmd, "./test %s &", argv[1]);	
					else sprintf(cmd, "./test &");
					system(cmd);
				}			
				else {
					printf("Already executed.\n");
				}
				break;
			case 'R':  //test프로세스 재시작
				if(objPID == -1) {
					printf("process 'test' isn't running.\nPlease use 'S'.\n");
				}
				else {
					printf("restart 'test'\n");
					sprintf(cmd, "kill -9 %d", objPID);
					system(cmd);
					if(argc == 2) sprintf(cmd, "./test %s &", argv[1]);	
					else sprintf(cmd, "./test &");
					system(cmd);

				}
				break;
			default:
				printf("Wrong command.\n");
				sleep(1);
				break;
		}	
		getchar();
	}

	exit(0);
}



int getObjPID(void)
{
	int buf0;//PID input
	char buf1[8];//tty input
	char buf2[16];//time input
	char buf3[64];//name input

	int isRunning = 0;
	int testPID = 0;

	FILE *fp;
	fp = popen("ps -e | grep test", "r");	
	while(!feof(fp)) {
		fscanf(fp, "%d%s%s%s", &buf0, buf1, buf2, buf3);
		//printf("%d %s %s %s\n", buf0, buf1, buf2, buf3);	
		if(strcmp(buf3, "test") == 0) {
			isRunning = 1;	
			testPID = buf0;
		}
	}
	pclose(fp);
	if(isRunning == 0) 
		return -1;
	
	return testPID;
}
void *t_function(void *arg)
{
	
	char cmd[16];
	int objPID;

	while(1) {

		objPID = getObjPID();

		if(objPID != -1) {
			printf("\nprocess 'test' is running. \n********info*********\n");
			sprintf(cmd, "\nps -fl %d", objPID);
			system(cmd);
		}
		else {
			printf("\ntest is terminated\n");
		}
		printf("Q:Quit, K:Kill, S:Start, R:Restart\n");
		printf(">> operator's command : \n");
		sleep(5);
	}
	pthread_exit(NULL);
}
