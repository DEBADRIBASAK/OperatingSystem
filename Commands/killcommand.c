//implementation of kill command
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
	if(argc<3)
	{
		printf("Usage: ./a.out signal_number pid\n");
		exit(0);
	}
	int k = kill(atoi(argv[2]),(pid_t)(atoi(argv[1]+1)));
	if(k==0)
	{
		printf("process received signal successfully\n");
	}
	else
	{
		printf("signal could not be sent\n");
	}
	return 0;
}