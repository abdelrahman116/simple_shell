#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
void unset_env_variable(char *args[]) {
    if (args[1] == NULL) {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
    } else {
        if (unsetenv(args[1]) != 0) {
            perror("unsetenv failed");
        }
    }
}
