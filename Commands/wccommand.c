#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define BUF_SIZE 256

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("Usage: ./a.out file_name\n");
		exit(0);
	}
	char buffer[BUF_SIZE];
	ssize_t sz;
	int open_fd;
	open_fd = open(argv[1],O_RDONLY);
	if(open_fd<0)
	{
		printf("error!\n");
		exit(0);
	}
	int char_count = 0,line_count = 0,word_count = 0;
	sz = read(open_fd,buffer,BUF_SIZE-1);
	int i;
	while((int)sz>0)
	{
		//printf("*");
		buffer[(int)sz] = '\0';
		for(i=0;i<sz;i++)
		{
			char_count++;
			if(buffer[i]=='\n')
			{
				word_count++;line_count++;
			}
			else if(buffer[i]==' ')
			{
				word_count++;
			}
		}
		sz = read(open_fd,buffer,BUF_SIZE-1);
	}
	printf("character count: %d\nword count: %d\nline count: %d\n",char_count,word_count,line_count);
	return 0;
}