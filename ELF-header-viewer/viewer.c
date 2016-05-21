#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void printBuf(char *buf, int size);

char info0[3][8] = {"unknown","ELF32","ELF64"};
char info1[3][16] = {"unknown","little-endian","big-endian"};
char info2[11][16] = {"unknown","System V","HP-UX","NetBSD","Linux","Solaris","AIX","IRIX","FreeBSD","OpenBSD","OpenVMS"};
char info3[6][24] = {"unknown","No file type","Relocatable file","Executable file","Shared object file", "Core file"};
char info4[11][16] = {"unknown","No specific","SPARC","x86","MIPS","PowerPC","ARM","SuperH","IA-64","x86-64","AArch64"};

int main(int argc, char **argv)
{
	int values[5];
	int version;
	int abiversion;
	int version2;
	long long entry;
	long long phoff;
	long long shoff;
	int flags;
	int ehsize;
	int phentsize;
	int phnum;
	int shentsize;
	int shnum;
	int shstrndx;
	
	int dword = 4;

	if(argc < 2) {
		perror("대상 파일을 지정하세요.\n");
		exit(1);
	}

	FILE *fp = fopen(argv[1], "rb");
	if(fp == NULL) {
		perror("올바른 파일을 지정하세요.\n");
		exit(1);
	}

	char buf[4];
	char buf1 = 0;
	short buf2 = 0;
	int buf4 = 0;
	long long buf8 = 0;
	int res;

	res = fread(buf, 4, 1, fp);
	if(res == 0 || buf[0]!=0x7F || buf[1]!='E' || buf[2]!='L' || buf[3]!='F') {
		perror("잘못된 ELF 매직넘버입니다.\n");
		exit(1);
	}
	

	fread(&buf1, 1, 1, fp);
	if(buf1 == 1) values[0] = 1;
	else if(buf1 == 2) { 
		values[0] = 2;
		dword = 8;
	}
	else values[0] = 0;

	fread(&buf1, 1, 1, fp);
	if(buf1 == 1) values[1] = 1;
	else if(buf1 == 2) values[1] = 2;
	else values[0] = 0;

	fread(&buf1, 1, 1, fp);
	version = buf1;

	fread(&buf1, 1, 1, fp);
	if(buf1 == 0x00) values[2] = 1;
	else if(buf1 == 0x01) values[2] = 2;
	else if(buf1 == 0x02) values[2] = 3;
	else if(buf1 == 0x03) values[2] = 4;
	else if(buf1 == 0x06) values[2] = 5;
	else if(buf1 == 0x07) values[2] = 6;
	else if(buf1 == 0x08) values[2] = 7;
	else if(buf1 == 0x09) values[2] = 8;
	else if(buf1 == 0x0C) values[2] = 9;
	else if(buf1 == 0x0D) values[2] = 10;
	else values[2] =  0;
	
	fread(&buf1, 1, 1, fp);
	abiversion = buf1;

	fread(&buf1, 1, 7, fp);
	
	fread(&buf2, 2, 1, fp);	
	if(buf2 == 0x00) values[3] = 1;
	else if(buf2 == 0x01) values[3] = 2;
	else if(buf2 == 0x02) values[3] = 3;
	else if(buf2 == 0x03) values[3] = 4;
	else if(buf2 == 0x04) values[3] = 5;
	else values[3] = 0;

	fread(&buf2, 2, 1, fp);
	if(buf2 == 0x00) values[4] = 1;
	else if(buf2 == 0x02) values[4] = 2;
	else if(buf2 == 0x03) values[4] = 3;
	else if(buf2 == 0x08) values[4] = 4;
	else if(buf2 == 0x14) values[4] = 5;
	else if(buf2 == 0x28) values[4] = 6;
	else if(buf2 == 0x2A) values[4] = 7;
	else if(buf2 == 0x32) values[4] = 8;
	else if(buf2 == 0x3E) values[4] = 9;
	else if(buf2 == 0xB7) values[4] = 10;
	else values[4] =  0;

	fread(&buf4, 4, 1, fp);
	version2 = buf4;
	
	fread(&buf8, dword, 1, fp);
	entry = buf8;

	fread(&buf8, dword, 1, fp);
	phoff = buf8;

	fread(&buf8, dword, 1, fp);
	shoff = buf8;
	
	fread(&buf4, 4, 1, fp);
	flags = buf4;
	
	fread(&buf2, 2, 1, fp);
	ehsize = buf2;
	fread(&buf2, 2, 1, fp);
	phentsize = buf2;
	fread(&buf2, 2, 1, fp);
	phnum = buf2;
	fread(&buf2, 2, 1, fp);
	shentsize = buf2;
	fread(&buf2, 2, 1, fp);
	shnum = buf2;
	fread(&buf2, 2, 1, fp);
	shstrndx = buf2;
	
	
	printf("\n");
	printf("%-36s%-20s\n","필드", "정보");
	printf("%-36s%-20s\n","ELF header","");
	printf("%-36s%-20s\n","Class",info0[values[0]]);
	printf("%-36s%-20s\n","Endian",info1[values[1]]);
	printf("%-36s%-20d\n","Version",version);
	printf("%-36s%-20s\n","OS/ABI",info2[values[2]]);
	printf("%-36s%-20d\n","ABI Version",abiversion);
	printf("%-36s%-20s\n","Type",info3[values[3]]);
	printf("%-36s%-20s\n","Machine",info4[values[4]]);
	printf("%-36s%-20d\n","ABI Version",version2);
	printf("%-36s%-20lld\n","Entry point addr",entry);
	printf("%-36s%-20lld\n","Program header offset",phoff);
	printf("%-36s%-20lld\n","Section header offset",shoff);
	printf("%-36s%-20d\n","Flags",flags);
	printf("%-36s%-20d\n","Elf header size",ehsize);
	printf("%-36s%-20d\n","Program header entry size",phentsize);
	printf("%-36s%-20d\n","Num of program header",phnum);
	printf("%-36s%-20d\n","Section header entry size",shentsize);
	printf("%-36s%-20d\n","Num of section header",shnum);
	printf("%-36s%-20d\n","Section header string table index",shstrndx);

	fclose(fp);
	exit(0);
}

void printBuf(char *buf, int size)
{
	int i;
	for(i=0; i<size; i++) {
		printf("%02X", buf[i]);
	}
}
