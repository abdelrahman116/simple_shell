#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGS 10

// Function to display the prompt
void print_prompt() {
    printf(":) ");
}

// Function to split the input command into arguments
int split_input(char *input, char *args[]) {
    int arg_count = 0;
    int i = 0;
    int len = strlen(input);

    while (i < len) {
        // Skip leading spaces or tabs
        while (i < len && (input[i] == ' ' || input[i] == '\t')) {
            i++;
        }

        // Found the start of an argument
        if (i < len) {
            char *start = &input[i];
            while (i < len && input[i] != ' ' && input[i] != '\t' && input[i] != '\n') {
                i++;
            }

            // Found the end of the argument
            char *end = &input[i];
            int arg_len = end - start;
            if (arg_len > 0) {
                args[arg_count] = (char *)malloc(arg_len + 1);
                strncpy(args[arg_count], start, arg_len);
                args[arg_count][arg_len] = '\0';
                arg_count++;
            }
        }
    }

    return arg_count;
}

// Function to execute the command
void execute_command(char *args[]) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("Command execution failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

// Function to set or modify an environment variable
void set_env_variable(char *args[]) {
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
    } else {
        if (setenv(args[1], args[2], 1) != 0) {
            perror("setenv failed");
        }
    }
}

// Function to unset an environment variable
void unset_env_variable(char *args[]) {
    if (args[1] == NULL) {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
    } else {
        if (unsetenv(args[1]) != 0) {
            perror("unsetenv failed");
        }
    }
}

// Function to change the current directory
void change_directory(char *args[]) {
    char *path = args[1];

    if (path == NULL) {
        // If no argument is given, change to $HOME
        path = getenv("HOME");
    } else if (strcmp(path, "-") == 0) {
        // Change to the previous directory
        path = getenv("OLDPWD");
    }

    char cwd[MAX_INPUT_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd failed");
        return;
    }

    // Save the current directory in OLDPWD
    if (setenv("OLDPWD", cwd, 1) != 0) {
        perror("setenv failed");
        return;
    }

    // Change to the new directory
    if (chdir(path) != 0) {
        perror("chdir failed");
    }

    // Update the PWD environment variable
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd failed");
        return;
    }
    if (setenv("PWD", cwd, 1) != 0) {
        perror("setenv failed");
        return;
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];

    while (1) {
        print_prompt();  // Display the prompt

        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Check for "end of file" condition (Ctrl+D)
            printf("\nExiting the shell.\n");
            break;
        }

        // Remove newline character from the input
        input[strcspn(input, "\n")] = '\0';

        // Split the input into arguments
        int arg_count = split_input(input, args);

        // Check if the user entered "exit"
        if (arg_count > 0 && strcmp(args[0], "exit") == 0) {
            printf("Exiting the shell.\n");
            // Free memory allocated for arguments
            for (int i = 0; i < arg_count; i++) {
                free(args[i]);
            }
            break;
        } else if (arg_count > 0 && strcmp(args[0], "setenv") == 0) {
            set_env_variable(args);
        } else if (arg_count > 0 && strcmp(args[0], "unsetenv") == 0) {
            unset_env_variable(args);
        } else if (arg_count > 0 && strcmp(args[0], "cd") == 0) {
            change_directory(args);
        } else {
            // Execute the command if it exists
            if (arg_count > 0) {
                if (access(args[0], X_OK) == 0) {
                    // The command exists in the current directory or full path
                    execute_command(args);
                } else {
                    // Search the PATH to find the command
                    char *path = getenv("PATH");
                    char path_copy[MAX_INPUT_LENGTH];
                    strcpy(path_copy, path);

                    char *dir = strtok(path_copy, ":");
                    char full_path[MAX_INPUT_LENGTH];

                    while (dir != NULL) {
                        snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);
                        if (access(full_path, X_OK) == 0) {
                            // Found the command in the directory
                            args[0] = full_path;
                            execute_command(args);
                            break;
                        }
                        dir = strtok(NULL, ":");
                    }

                    if (dir == NULL) {
                        printf("Command not found: %s\n", args[0]);
                    }
                }
            }
        }

        // Free memory allocated for arguments
        for (int i = 0; i < arg_count; i++) {
            free(args[i]);
        }
    }

    return 0;
}

