#include "shell.h"

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
