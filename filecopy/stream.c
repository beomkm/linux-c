#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 8192

int main()
{
	FILE *in, *out;
	char buf[BUF_SIZE];
	int nread;

	in = fopen("file.in", "r");
	out = fopen("file.out", "w");

	if(in != NULL && out != NULL) {
		while(!feof(in)) {
			nread = fread(buf, 1, BUF_SIZE, in);
			fwrite(buf,1, nread, out);
		}
		fclose(in);
		fclose(out);
	}

	exit(0);
}



