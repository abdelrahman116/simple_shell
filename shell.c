#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *_getenv(const char *name)
{
    extern char **environ;

    int i = 0;
    while (environ[i] != NULL)
    {
        char *key = strtok(environ[i], "=");
        char *value = strtok(NULL, "=");

        if (strcmp(key, name) == 0)
            return value;

        i++;
    }

    return NULL;
}

void shell_0_1(void)
{
    char buffer[BUFFER_SIZE];
    ssize_t read_size;
    char *command;
    char *args[BUFFER_SIZE];
    int i;
    pid_t pid = fork();

    while (1)
    {
        char *prompt = _getenv("USER");
        if (prompt)
            write(1, prompt, strlen(prompt));
        else
            write(1, "$ ", 2);

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
            return;
        }
        else
        {
            wait(NULL);
        }
    }
}

void shell_0_2(void)
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
            return;
        }
        else
        {
            wait(NULL);
        }
    }
}

void shell_0_3(void)
{
    char buffer[BUFFER_SIZE];
    ssize_t read_size;
    char *command;
    char *args[BUFFER_SIZE];
    int i;
    pid_t pid = fork();
    char *path = _getenv("PATH");
    char *token = strtok(path, ":");

    while (1)
    {
        char *prompt = _getenv("USER");
        if (prompt)
            write(1, prompt, strlen(prompt));
        else
            write(1, ":) ", 3);

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

        if (pid == 0)
        {
            if (path == NULL)
            {
                perror("Error: PATH environment variable not found");
                exit(EXIT_FAILURE);
            }

            while (token)
            {
                char command_path[BUFFER_SIZE];
                snprintf(command_path, BUFFER_SIZE, "%s/%s", token, command);
                execvp(command_path, args);
                token = strtok(NULL, ":");
            }


            perror("Error: Command not found");
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("Error");
            return;
        }
        else
        {
            wait(NULL);
        }
    }
}

