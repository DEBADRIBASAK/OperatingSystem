#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int is_num(char *a)
{
	int i=0;
	for(i=0;i<strlen(a);i++)
	{
		if(a[i]<'0'||a[i]>'9')
			return 0;
	}
	return 1;
}

int main(int argc,char* argv[])
{
	DIR *drptr = opendir("/proc");
	struct dirent *drnt = readdir(drptr);
	char buffer[5];
	while(drnt!=NULL)
	{
		char *helper = NULL;
		if(is_num(drnt->d_name))
		{
			printf("%s ",drnt->d_name);
			helper = (char*)malloc(sizeof(char));
			strcpy(helper,"/proc/");
			strcat(helper,drnt->d_name);
			strcat(helper,"/status");
			int fd = open(helper,O_RDONLY);
			if(fd<0)
			{
				perror("ERROR");
			}
			read(fd,buffer,(size_t)4);
			buffer[4] = '\0';
			read(fd,buffer,(size_t)1);
			buffer[1] = '\0';
			while(buffer[0]!='\n')
			{
				//printf("%c",buffer[0]);
				printf("%s",buffer);
				read(fd,buffer,1);
				buffer[1] = '\0';
			}
			printf("\n");
			close(fd);
		}
		drnt = readdir(drptr);
	}
	closedir(drptr);
	return 0;
}