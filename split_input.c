#include <string.h>
#include <stdlib.h>
#include "shell.h"

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
