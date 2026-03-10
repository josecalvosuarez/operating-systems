/*
 * 01_command_line_args.c
 * 
 * TOPIC: Command Line Arguments
 * 
 * DESCRIPTION:
 * This program demonstrates how to accept and process command-line arguments
 * in C. It shows how argc (argument count) and argv (argument vector) provide
 * access to arguments passed to a program from the shell.
 * 
 * LEARNING OBJECTIVES:
 * - Understand argc and argv parameters
 * - Parse command-line arguments
 * - Demonstrate different types of argument processing
 * 
 * USAGE:
 *   gcc -o 01_command_line_args 01_command_line_args.c
 *   ./01_command_line_args hello world 42
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /*
     * argc: argument count (includes the program name)
     * argv: argument vector (array of strings containing the arguments)
     */

    printf("=== Command Line Arguments Demo ===\n\n");

    /* Display total number of arguments */
    printf("Total arguments (argc): %d\n", argc);
    printf("Program name (argv[0]): %s\n\n", argv[0]);

    /* Option 1: Display all arguments */
    printf("All arguments:\n");
    for (int i = 0; i < argc; i++) {
        printf("  argv[%d]: %s\n", i, argv[i]);
    }

    /* Option 2: Process specific arguments (if provided) */
    printf("\n");
    if (argc > 1) {
        printf("First argument after program name: %s\n", argv[1]);
    } else {
        printf("No arguments provided (other than program name)\n");
    }

    /* Option 3: Convert argument to integer */
    printf("\n");
    if (argc > 2) {
        int number = atoi(argv[2]);
        printf("Second argument as integer: %d\n", number);
        printf("That number doubled: %d\n", number * 2);
    }

    /* Option 4: Check for specific number of arguments */
    printf("\n");
    if (argc == 4) {
        printf("Exactly 3 arguments were provided (not counting program name)\n");
        printf("Arg 1: %s, Arg 2: %s, Arg 3: %s\n", argv[1], argv[2], argv[3]);
    } else if (argc > 4) {
        printf("More than 3 arguments provided\n");
    } else if (argc < 4) {
        printf("Fewer than 3 arguments provided\n");
    }

    return 0;
}
