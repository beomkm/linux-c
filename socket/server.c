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
	int s_sock, c_sock;
	char msg[BUF_SIZE];
	int result, i;
	int recv_cnt, recv_len;

	struct sockaddr_in s_addr, c_addr;
	socklen_t c_addr_size;


	if(argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	
	s_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(s_sock == -1)
		err_h("socket() error");

	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_port = htons(atoi(argv[1]));

	if(bind(s_sock, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1)
		err_h("bind() error");

	if(listen(s_sock, 5) == -1)
		err_h("listen() error");

	c_addr_size = sizeof(c_addr);

	
	for(i=0; i<5; i++) {
		puts("Waiting for client.....");
		c_sock = accept(s_sock, (struct sockaddr *)&c_addr, &c_addr_size);
		puts("Accepted");
		read(c_sock, msg, BUF_SIZE);
		write(c_sock, msg, BUF_SIZE);
		close(c_sock);
	}
	close(s_sock);
	return 0;
}



void err_h(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

