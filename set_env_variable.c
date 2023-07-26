#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

void set_env_variable(char *args[]) {
	    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
    } else {
        if (setenv(args[1], args[2], 1) != 0) {
            perror("setenv failed");
        }
    }
}

