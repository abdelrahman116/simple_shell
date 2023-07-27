#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>   // Add this for strtok

#define BUFFER_SIZE 1024

/**
 * execute_command - Execute a single command with arguments
 * @command: The command to be executed
 * @args: An array of arguments, including the command itself
 * Return: On success, returns 0. On failure, returns -1.
 */
int execute_command(char *command, char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execvp(command, args) == -1)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /* Fork failed */
        perror("Error");
        return (-1);
    }
    else
    {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return (0);
}

/**
 * main - Simple shell main function
 * Return: Always 0.
 */
int main(void)
{
    while (1)
    {
        write(1, "$ ", 2);
        char buffer[BUFFER_SIZE];
        ssize_t read_size = read(0, buffer, BUFFER_SIZE);
        if (read_size <= 0)
            break;

        /* Null-terminate the input string */
        buffer[read_size - 1] = '\0';  // To remove the newline character

        /* Split the input into command and arguments */
        char *command = strtok(buffer, " \t\n");
        if (command == NULL)
            continue;

        /* Prepare arguments array */
        char *args[BUFFER_SIZE];  // Increase buffer size to avoid potential issues

        int i = 0;  // Initialize 'i' to 0 instead of 1
        while (i < BUFFER_SIZE)
        {
            args[i] = strtok(NULL, " \t\n");
            if (args[i] == NULL)
                break;
            i++;
        }
        args[i] = NULL;

        execute_command(command, args);
    }

    return (0);
}

