#ifndef SHELL_H
#define SHELL_H
#define MAX_INPUT_LENGTH 100
#define MAX_ARGS 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void print_prompt();
int split_input(char *input, char *args[]);
void execute_command(char *args[]);
void set_env_variable(char *args[]);
void unset_env_variable(char *args[]);
void change_directory(char *args[]);

#endif
