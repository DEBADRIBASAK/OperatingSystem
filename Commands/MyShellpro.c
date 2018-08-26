/**
This is a shell for executing some commands
the commands are also implemented manually
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

int main(int argc,char* argv[])
{
	char command[100],buffer[100];
	int fd,cfd,rfd,fd2,sz;
	int num_args;
	printf("This is a shell developed by KRD ... type \"helpme\" for instructions\n");
	while(1)
	{
		printf(">>>");
		cfd = dup(1);
		//rfd = dup(0);
		fd = -1;//fd2 = -1;
		char helper[3] = {'.','/','\0'};
		scanf("%[^\n]s",command);
		strcpy(buffer,command);
		//printf("buffer1 = %s\n",buffer);
		num_args = 0;
		char *tok;
		tok = strtok(command," ");
		while(tok!=NULL)
		{
			//printf("buffer1 = %s\n",buffer);
			if(tok[0]=='>')
			{
				if(tok[1]=='>')
				{
					fd = open(tok+2,O_WRONLY|O_CREAT|O_APPEND|O_TRUNC,S_IRUSR|S_IRGRP|S_IWUSR|S_IWGRP);
				}
				else
				{
					fd = open(tok+1,O_WRONLY|O_CREAT,S_IRUSR|S_IRGRP|S_IWUSR|S_IWGRP);
				}
				if(fd<0)
				{
					perror("Problem with output redirection");
					exit(0);
				}
				//dup2(1,cfd);

			}
			else if(tok[0]=='<')
			{
				//char arr[10];
				FILE *fp;
				fp = fopen(tok+1,"r");
				if(fp==NULL)
				{
					perror("Problem with input redirection");
					exit(0);
				}
				//dup2(fd2,0);
				//sz = fscanf(fp,"%s",arr);
				char ch;
				ch = fgetc(fp);
				while(ch!=EOF)
				{
					if(ch==' '||ch=='\n')
					num_args++;
					//sz = fscanf(fp,"%s",arr);
					ch = fgetc(fp);
				}
				fclose(fp);
			}
			else
			{
				num_args++;
			}
			//printf("buffer2 = %s\n",buffer);
			tok = strtok(NULL," ");
		}
		if(num_args==0)
		{
			while((getchar())!='\n');
			continue;
		}
		//printf("num_args = %d\n",num_args);
		char *process[num_args+1];
		int i;
		for(i=0;i<num_args+1;i++)
		{
			process[i] = (char*)malloc(sizeof(char));
		}
		tok = NULL;
		//printf("buffer = %s\n",buffer);
		tok = strtok(buffer," ");
		//printf("token = %s\n",tok);
		if(num_args==1&&strcmp(tok,"exit")==0)
		{
			exit(0);
		}
		if(num_args==1&&strcmp(tok,"cls")==0)
		{
			system("clear");
			while((getchar())!='\n');
			continue;
		}
		strcat(helper,tok);
		//printf("helper = %s\n",helper);
		int i1 = 1,status;
		//printf("***********\n");
		strcpy(process[0],helper);
		while(tok!=NULL)
		{
			//printf("+\n");
			tok = strtok(NULL," ");
			if(tok==NULL)
				break;
			else if(tok[0]!='>'&&tok[0]!='<')
			{
				strcpy(process[i1],tok);
				i1++;
			}
			else if(tok[0]=='<')
			{
				char arr[10];
				FILE *fd3;
				//printf("kjxjgSJCAD\n");
				fd3 = fopen(tok+1,"r");//O_RDONLY);
				if(fd3==NULL)
				{
					perror("ERROR");
					exit(0);
				}
				//dup2(fd3,0);
				//printf("upto this\n");
				sz = 0;char ch;
				ch = fgetc(fd3);
				while(ch!=EOF&&ch!=' '&&ch!='\n')
				{
					arr[sz]= ch;
					sz++;
					ch = fgetc(fd3);
				}
				while(sz>0)
				{
					arr[sz] = '\0';
					//printf("arr = %s\n",arr);
					strcpy(process[i1],arr);
					i1++;
					sz = 0;
					ch = fgetc(fd3);
					while(ch!=EOF&&ch!=' '&&ch!='\n')
					{
						arr[sz]= ch;
						sz++;
						ch = fgetc(fd3);
					}
				}
				fclose(fd3);
			}
		}
		process[i1] = NULL;
		// int m;
		// for(m=0;m<i1;m++)
		// {
		// 	printf("pro = %s\n",process[m]);
		// }
		char* a[1] = {NULL};
		if(fd!=-1)
		{
			dup2(fd,1);
		}
		pid_t pid;
		pid = fork();
		if(pid==0)
		{
			//printf("helper= %s\n",helper);
			int h = execve(process[0],process,a);
			if(h==-1)
			{
				perror("ERROR!!!!!!");
			}
			printf("child returned!\n");
			exit(0);
		}
		else
		{
			do
			{
				wait(&status);
			}while(!WIFEXITED(status)&&!WIFSIGNALED(status));
			while((getchar())!='\n');
			if(fd!=-1)
			{
				//close(fd);
				dup2(cfd,1);
				close(cfd);
				close(fd);
			}
		}
		int j;
		for(j=0;j<num_args+1;j++)
		{
			//printf("Upto Here\n");
			process[j] = NULL;
		}
		//strcpy(command,"***");
		command[0] = '\0';
	}
	return 0;
}