#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void err_h(char *msg);

int main(int argc,char **argv)
{
	int sock;
	char msg[BUF_SIZE];
	int str_len;
	struct sockaddr_in s_addr;

	if(argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		err_h("socket() error");

	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = inet_addr(argv[1]); 
	s_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1)
		err_h("connect() error");
	else
		puts("Connected..");

	while(1) {
		fputs("Input message(Q to quit): ", stdout);
		fgets(msg, BUF_SIZE, stdin);

		if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
			break;

		write(sock, msg, strlen(msg));
		str_len = read(sock, msg, BUF_SIZE-1);
		msg[str_len] = 0;
		printf("Msg from server : %s", msg);
	}
	close(sock);

	return 0;
}

void err_h(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

