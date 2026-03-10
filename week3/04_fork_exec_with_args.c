/*
 * 04_fork_exec_with_args.c
 * 
 * TOPIC: Passing Arguments with fork() and exec()
 * 
 * DESCRIPTION:
 * This program demonstrates how to pass command-line arguments from a parent
 * process to a child process that will execute a different program using exec().
 * It shows how to construct argument arrays and pass them to the executed program.
 * 
 * LEARNING OBJECTIVES:
 * - Understand how to construct argument arrays for exec()
 * - Learn to pass parent's arguments to child process
 * - Understand execvp() (vector-based exec with PATH lookup)
 * - Learn proper argument array construction with NULL terminator
 * 
 * INCLUDES:
 * - unistd.h: For fork(), execvp(), wait()
 * - stdio.h: For printf()
 * - stdlib.h: For malloc(), free()
 * - string.h: For string operations
 * - sys/types.h: For pid_t
 * 
 * EXECUTION:
 *   Parent constructs argument array -> forks -> child execs program with args
 * 
 * USAGE:
 *   gcc -o 04_fork_exec_with_args 04_fork_exec_with_args.c
 *   ./04_fork_exec_with_args echo Hello World
 *   ./04_fork_exec_with_args cat /etc/hostname
 *   ./04_fork_exec_with_args grep main 04_fork_exec_with_args.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    printf("=== fork() and exec() with Arguments Demo ===\n\n");

    /* Validate arguments */
    if (argc < 2) {
        printf("Usage: %s <program> [args...]\n", argv[0]);
        printf("Example: %s echo Hello World\n", argv[0]);
        printf("Example: %s cat /etc/hostname\n", argv[0]);
        return 1;
    }

    pid_t my_pid = getpid();
    const char *program = argv[1];  /* Program to execute */

    printf("[Parent PID: %d] Program to execute: %s\n", my_pid, program);
    printf("[Parent PID: %d] Arguments (argc=%d):\n", my_pid, argc - 1);
    
    for (int i = 1; i < argc; i++) {
        printf("  argv[%d]: %s\n", i - 1, argv[i]);
    }

    printf("\n");

    /* === Construct argument array for exec() === */
    /*
     * We need to create an array of strings to pass to execvp():
     * - argv_exec[0] = program name
     * - argv_exec[1..n] = arguments
     * - argv_exec[n+1] = NULL (required terminator)
     * 
     * argc=3 means: program, arg1, arg2
     * We need argc pointers in the array + 1 for NULL
     */
    char **argv_exec = malloc(argc * sizeof(char *));
    if (argv_exec == NULL) {
        perror("malloc() failed");
        return 1;
    }

    /* Copy arguments to new array (skip argv[0] which is our program name) */
    for (int i = 1; i < argc; i++) {
        argv_exec[i - 1] = argv[i];
    }
    argv_exec[argc - 1] = NULL;  /* NULL terminator (required for exec) */

    printf("[Parent PID: %d] Exec argument array constructed\n", my_pid);
    printf("[Parent PID: %d] Now forking...\n\n", my_pid);

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork() failed");
        free(argv_exec);
        return 1;
    }

    if (child_pid == 0) {
        /* === CHILD PROCESS === */
        printf("[Child PID: %d] Child started\n", getpid());
        printf("[Child PID: %d] About to execute: %s\n", getpid(), program);
        printf("[Child PID: %d] --- Program output begins ---\n\n", getpid());

        /*
         * execvp() system call:
         * - execvp(filename, argv_array)
         * - filename: program name (searched in PATH)
         * - argv_array: pointer to NULL-terminated array of arguments
         * 
         * The argv array should have:
         *   argv[0] = program name (usually argv[1] from parent)
         *   argv[1..n] = arguments
         *   argv[n+1] = NULL
         */
        execvp(program, argv_exec);

        /* execvp() only returns if there's an error */
        perror("execvp() failed");
        free(argv_exec);
        exit(1);

    } else {
        /* === PARENT PROCESS === */
        printf("[Parent PID: %d] Child forked with PID: %d\n", getpid(), child_pid);
        printf("[Parent PID: %d] Waiting for child...\n", getpid());

        /* Wait for child */
        int status;
        pid_t completed_pid = wait(&status);

        printf("\n[Parent PID: %d] --- Program output ends ---\n\n", getpid());
        printf("[Parent PID: %d] Child (PID: %d) completed\n", getpid(), completed_pid);
        printf("[Parent PID: %d] Child exit status: %d\n", getpid(), status);

        printf("[Parent PID: %d] Cleanup: freeing argv_exec\n", getpid());
        free(argv_exec);
    }

    printf("[PID: %d] Done\n\n", getpid());
    return 0;
}
