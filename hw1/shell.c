#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#define STD_INPUT 0
#define STD_OUTPUT 1
static void type_prompt()
{
	printf("Please input a command\n$");
}
int read_command(char* command,char* command2,char* parameters[],char inputstring[],char AND,int read)
{
	int i,LENGTH;
	const int INPUT=100;
	fgets(inputstring,INPUT,stdin);
	LENGTH=strlen(inputstring)-1;
	AND=inputstring[LENGTH-1];
	inputstring[LENGTH]='\0';
	if(AND=='&')
	{
		inputstring[LENGTH-1]='\0';
	}
	parameters[0]=strtok(inputstring," ");
	for(i=1;i<100;++i)
	{	
		parameters[i] = strtok(NULL," ");
        	if (parameters[i]==NULL) 
            	break;
	}
	strcpy(command,parameters[0]);
	if(parameters[1]!=NULL)
	{
		strcpy(command2,parameters[1]);
	}
	if(AND=='&')
	{
		return 1;
	}
	else return 0;
}
void single_process(char* command,char* parameters[],char inputstring[])
{
	if(execvp(command,parameters)==-1)
	{
		printf("Command not found\n");
		return -1;
	}
}
void two_process_pipeline(char* parameters[])
{
	int fd[2];
	char *process1,*process2;
	process1=parameters[0];
	process2=parameters[2];
	if(pipe(fd)==-1)
	{
		printf("Error!Unable to create pipe");
		exit(0);
	}
	if(fork()!=0)
	{
		close(fd[0]);
		close(STD_OUTPUT);
		dup(fd[1]);
		close(fd[1]);
		execl(process1,process1,0);
	}
	else
	{
		close(fd[1]);
		close(STD_INPUT);
		dup(fd[0]);
		close(fd[0]);
		execl(process2,process2,0);
	}

}

int simple_terminal()
{
	
	while(1)
	{
		int status=0,read=0,LENGTH,yn;
		char *filename,*parameters[100],command[100]={0},inputstring[100]={0},command2[100]={0},AND;
		type_prompt();	
		yn=read_command(command,command2,parameters,inputstring,AND,read);
		if(yn==0)
		{
			if(fork()!=0)
			{
				waitpid(-1,&status,0);
			}
			else
			{
				if(command2[0]=='>')
				{			
					int file;
					file=open(filename,O_RDONLY);
					dup2(file,STD_INPUT);
					execvp(command,parameters);
					close(file);	
				}
				else 
				{
					single_process(command,parameters,inputstring);
				}
			}	
		}
		else if(yn==1)
		{
			printf("Success to background!");
			if(fork()!=0)
			{

			}
			else
			{
				if(command2[0]=='>')
				{			
					int file;
					file=open(filename,O_RDONLY);
					dup2(file,STD_INPUT);
					execvp(command,parameters);
					close(file);	
				}
				else 
				{
					single_process(command,parameters,inputstring);
				}
			}	
		}	
	}
}

