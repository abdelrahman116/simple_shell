#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_INPUT_LENGTH 100
#define MAX_ARGS 10

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

        // ... (rest of the main function as before)
    }

    return 0;
}

