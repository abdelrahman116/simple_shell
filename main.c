#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_INPUT_LENGTH 100
#define MAX_ARGS 10

int main(void)
{

    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];

    while (1)
    {
        print_prompt();  // Display the prompt

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            // Check for "end of file" condition (Ctrl+D)
            printf("\nExiting the shell.\n");
            break;
        }

        // Remove newline character from the input
        input[strcspn(input, "\n")] = '\0';

        // Split the input into arguments
        int arg_count = split_input(input, args);

        // Check if the user entered "exit"
        if (arg_count > 0 && strcmp(args[0], "exit") == 0)
        {
            // Free memory allocated for arguments
            for (int i = 0; i < arg_count; i++)
            {
                free(args[i]);
            }
            printf("\n");
            break;
        }
        else if (arg_count > 0)
        {
            // ... (rest of the execution logic for commands)
            execute_command(args);
        }

        // Free memory allocated for arguments
        for (int i = 0; i < arg_count; i++)
        {
            free(args[i]);
        }
    }

    return 0;
}

