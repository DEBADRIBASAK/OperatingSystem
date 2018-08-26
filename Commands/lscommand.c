#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("usage: ./a.out file_name\n");
		exit(0);
	}
	DIR *drptr = opendir(argv[1]);
	struct dirent *drnt = readdir(drptr);
	while(drnt!=NULL)
	{
		printf("%s\n",drnt->d_name);
		drnt = readdir(drptr);
	}
	closedir(drptr);
	return 0;
}
