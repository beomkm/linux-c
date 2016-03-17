#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
	time_t timer;
	struct tm *t;
	char tty[16];

	FILE* fp;
	
	timer = time(NULL);
	t = localtime(&timer);

	if(argc == 2) {
		strcpy(tty, argv[1]);
		fp = fopen(tty, "w");
	}
	else fp = stdout;

	fprintf(fp, "program 'test'\n");
	while(1) {
		timer = time(NULL);
		t = localtime(&timer);
		fprintf(fp, "%d시 %d분 %d초\n", t->tm_hour, t->tm_min, t->tm_sec);
		sleep(2);
	}
	fclose(fp);
	exit(0);
}
