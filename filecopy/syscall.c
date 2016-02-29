#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUF_SIZE 8192

int main()
{
	char block[BUF_SIZE];
	int in, out;
	int nread;

	in = open("file.in", O_RDONLY);
	out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

	if(in == -1 || out == -1) exit(1);
	

	while((nread = read(in, block, sizeof(block))) > 0)
		write(out, block, nread);

	close(in);
	close(out);

	exit(0);
}
	
