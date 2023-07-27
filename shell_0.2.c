#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char buffer[BUFFER_SIZE];
    ssize_t read_size;
    char *command;
    char *args[BUFFER_SIZE];
    int i;
    pid_t pid;

    while (1)
    {
        write(1, "#cisfun$ ", 9);

        read_size = read(0, buffer, BUFFER_SIZE);
        if (read_size <= 0)
            break;

        buffer[read_size - 1] = '\0';

        if (strcmp(buffer, "exit") == 0)
            break;

        command = strtok(buffer, " \t\n");
        if (command == NULL)
            continue;

        i = 0;
        while (i < BUFFER_SIZE)
        {
            args[i] = strtok(NULL, " \t\n");
            if (args[i] == NULL)
                break;
            i++;
        }
        args[i] = NULL;

        pid = fork();
        if (pid == 0)
        {
            if (execvp(command, args) == -1)
            {
                perror("Error");
                exit(EXIT_FAILURE);
            }
        }
        else if (pid < 0)
        {
            perror("Error");
            return (-1);
        }
        else
        {
            wait(NULL);
        }
    }

    return (0);
}

