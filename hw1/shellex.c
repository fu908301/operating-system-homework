#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void type_porompt()
{
    printf("> ");
}

static void read_command(char* command, char* parameters[])
{
    const int MAX_CHAR_INPUT = 1000;
    const int MAX_ARG = 100;
    char inputString[MAX_CHAR_INPUT];
    int i;
    fgets(inputString, MAX_CHAR_INPUT, stdin);
    inputString[strlen(inputString) - 1] = '\0';    //Remove the newline character
    
    parameters[0] = strtok(inputString, " ");

    if (strcmp(parameters[0], "exit") == 0) {
        puts("Exit from the shell...");
        exit(0);
    }
    
    for (i = 1; i < MAX_ARG; ++i) {
        parameters[i] = strtok(NULL, " ");
        if (parameters[i] == NULL) {
            break;
        }
    }
    
    strcpy(command, parameters[0]);
}

int simple_terminal() {
    puts("Shell is started");
    puts("===========================");
    
    while(1) {
        char command[100];
        char* parameters[100];
        int status = 0;
        
        type_porompt();
        read_command(command, parameters);
	printf("%s%s%d%d\n",parameters[0],parameters[1],parameters[2],parameters[3]);
        
        if (fork() != 0) {  //Parent
            waitpid(-1, &status, 0);
        } else {            //Child
            if (execvp(command, parameters) == -1) {
                puts("Command invalid.");
                return -1;
            }
        }
    }
    
    return 0;
}
