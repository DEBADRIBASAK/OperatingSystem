#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("Usage: ./a.out file_name\n");
		exit(0);
	}
	char helper[3] = {'.','/','\0'};
	strcat(helper,argv[1]);
	int err;
	err = unlink(helper);
	if(err==0)
	{
		printf("file successfully deleted\n");;
	}
	else
	{
		printf("could not delete file!\n");
	}
	return 0;
}