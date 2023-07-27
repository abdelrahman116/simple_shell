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

        pid = fork();
        if (pid == 0)
        {
            if (execve(buffer, (char *const *)&buffer, NULL) == -1)
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

