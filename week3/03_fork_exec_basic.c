/*
 * 03_fork_exec_basic.c
 * 
 * TOPIC: Process Execution with fork() and exec()
 * 
 * DESCRIPTION:
 * This program demonstrates how to use fork() combined with exec() functions
 * to create a child process and then replace its image with a different program.
 * The exec() family of functions allow a process to replace its code, data, and
 * heap with a new program while keeping the same PID.
 * 
 * Different exec variants:
 * - execl():  Takes list of arguments (variadic)
 * - execp():  Searches PATH environment variable
 * - execv():  Takes array of arguments
 * - execlp(): Combines execl() and execp()
 * - execvp(): Combines execv() and execp() [most commonly used]
 * 
 * LEARNING OBJECTIVES:
 * - Understand fork() and exec() combination pattern
 * - Learn different exec() variants
 * - Understand program execution model
 * - Learn to pass arguments to executed programs
 * - Understand that exec() replaces the process image
 * 
 * INCLUDES:
 * - unistd.h: For fork(), execl(), execlp(), wait()
 * - stdio.h: For printf()
 * - sys/types.h: For pid_t
 * 
 * EXECUTION SEQUENCE:
 *   1. Parent forks child
 *   2. Child calls exec() to run external program
 *   3. Child's image replaced with new program
 *   4. Parent waits for child to complete
 *   5. Both processes exit
 * 
 * USAGE:
 *   gcc -o 03_fork_exec_basic 03_fork_exec_basic.c
 *   ./03_fork_exec_basic
 *   ./03_fork_exec_basic "Hello from exec"
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    printf("=== fork() and exec() Demo ===\n\n");

    pid_t my_pid = getpid();
    printf("[Parent PID: %d] About to fork and execute 'ls' command\n\n", my_pid);

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork() failed");
        return 1;
    }

    if (child_pid == 0) {
        /* === CHILD PROCESS === */
        printf("[Child PID: %d] Child process started\n", getpid());
        printf("[Child PID: %d] About to execute external program\n\n", getpid());
        printf("[Child PID: %d] --- Beginning of ls output ---\n", getpid());

        /*
         * execlp() system call (exec + PATH lookup):
         * - execlp(filename, arg0, arg1, ..., NULL)
         * - filename: program to execute (searched in PATH)
         * - arg0: program name (usually same as filename)
         * - arg1...argN: command-line arguments
         * - Last argument MUST be NULL to terminate the list
         * 
         * Examples of exec variants:
         *   execl("/bin/ls", "ls", "-la", NULL);     // exact path
         *   execlp("ls", "ls", "-la", NULL);         // search PATH
         *   execv("/bin/ls", argv_array);            // use array
         */
        execlp("ls", "ls", "-la", NULL);  /* Execute 'ls -la' command */

        /*
         * Code after exec() only runs if exec() fails!
         * If exec() succeeds, it replaces the process image
         */
        perror("execlp() failed");  /* This only prints if exec() fails */
        exit(1);

    } else {
        /* === PARENT PROCESS === */
        printf("\n[Parent PID: %d] Child forked with PID: %d\n", getpid(), child_pid);
        printf("[Parent PID: %d] Parent waiting for child to complete...\n\n", getpid());

        /* Wait for child to complete */
        int status;
        pid_t completed_pid = wait(&status);

        printf("\n[Parent PID: %d] --- End of ls output ---\n", getpid());
        printf("[Parent PID: %d] Child process (PID: %d) has completed\n", getpid(), completed_pid);
        printf("[Parent PID: %d] Child exit status: %d\n", getpid(), status);

        printf("[Parent PID: %d] Parent continuing after child completion\n", getpid());
    }

    printf("[PID: %d] Exiting\n", getpid());
    return 0;
}
