#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 256
int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("Usage: ./a.out file_name1***************\n");
		printf("%d %s\n",argc,argv[0]);
		exit(0);
	}
	int open_fd;	
	open_fd = open(argv[1],O_RDONLY);
	char buffer[BUF_SIZE];
	int sz;
	sz = read(open_fd,buffer,BUF_SIZE-1);
	while(sz>0)
	{
		buffer[sz] = '\0';
		write(1,buffer,sz);
		sz = read(open_fd,buffer,BUF_SIZE-1);
	}
	return 0;
}
