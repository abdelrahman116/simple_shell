#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

void check_betty_style(const char *filename) {
    char command[MAX_COMMAND_LENGTH];
    snprintf(command, MAX_COMMAND_LENGTH, "betty-style %s", filename);

    int status = system(command);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        printf("%s follows the Betty style.\n", filename);
    } else {
        printf("%s does not follow the Betty style.\n", filename);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    check_betty_style(filename);

    return 0;
}

