#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

void check_betty_style(const char *filename)
 {
    char command[MAX_COMMAND_LENGTH];
    int status = system(command);

    snprintf(command, MAX_COMMAND_LENGTH, "betty-style %s", filename);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        printf("%s follows the Betty style.\n", filename);
    } else {
        printf("%s does not follow the Betty style.\n", filename);
    }
}

int main(int argc, char *argv[]) {
    
    char *filename = argv[1];

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }


    check_betty_style(filename);

    return 0;
}

