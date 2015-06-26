#ifdef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
static void type_prompt();
int read_command(char* command,char* command2,char* parameters[],char inputstring[],char AND,int read);
int single_process(char* command,char* parameters[],char inputstring[]);
void two_process_pipeline(char* parameters[]);
int  simple_terminal();
#endif
