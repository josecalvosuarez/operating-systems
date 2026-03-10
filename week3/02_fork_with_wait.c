/*
 * 02_fork_with_wait.c
 * 
 * TOPIC: Process Creation and Synchronization with fork() and wait()
 * 
 * DESCRIPTION:
 * This program builds on 01_basic_fork.c by adding process synchronization
 * using wait(). The wait() call causes the parent process to block (pause)
 * until a child process terminates, allowing proper process management.
 * This prevents zombie processes and ensures coordinated execution.
 * 
 * LEARNING OBJECTIVES:
 * - Understand wait() for process synchronization
 * - Learn about zombie processes and why they occur
 * - Understand parent-child process coordination
 * - Learn WIFEXITED() and WEXITSTATUS() macros for exit status
 * 
 * INCLUDES:
 * - unistd.h: For fork(), getpid(), sleep(), wait()
 * - stdio.h: For printf()
 * - sys/types.h: For pid_t type
 * 
 * EXECUTION SEQUENCE:
 *   1. Parent forks child
 *   2. Parent and child run concurrently
 *   3. Parent calls wait() and blocks
 *   4. Child completes and exits
 *   5. wait() returns with child's exit status
 *   6. Parent continues and exits
 * 
 * USAGE:
 *   gcc -o 02_fork_with_wait 02_fork_with_wait.c
 *   ./02_fork_with_wait
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    printf("=== fork() with wait() Demo ===\n\n");

    pid_t my_pid = getpid();
    printf("[Parent PID: %d] Starting fork demo\n\n", my_pid);

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork() failed");
        return 1;
    }

    if (child_pid == 0) {
        /* === CHILD PROCESS === */
        printf("[Child PID: %d] Child process started\n", getpid());
        printf("[Child PID: %d] Parent's PID: %d\n", getpid(), getppid());
        printf("[Child PID: %d] Child is working...\n", getpid());

        /* Simulate work with sleep */
        sleep(2);

        printf("[Child PID: %d] Child work completed\n", getpid());
        printf("[Child PID: %d] Child exiting with status 42\n", getpid());
        
        exit(42);  /* Child exits with status 42 */

    } else {
        /* === PARENT PROCESS === */
        printf("[Parent PID: %d] Child created with PID: %d\n", getpid(), child_pid);
        printf("[Parent PID: %d] Parent is waiting for child to complete...\n", getpid());

        /*
         * wait() system call:
         * - Blocks parent until child process terminates
         * - Returns child's PID if successful, -1 on error
         * - status parameter receives child's exit information
         */
        int status;  /* Variable to store child's exit status */
        pid_t completed_pid = wait(&status);

        if (completed_pid == -1) {
            perror("wait() failed");
            return 1;
        }

        printf("\n[Parent PID: %d] Child process has completed\n", getpid());
        printf("[Parent PID: %d] wait() returned for child PID: %d\n", getpid(), completed_pid);
        printf("[Parent PID: %d] Child exit status: %d\n", getpid(), status);

        printf("[Parent PID: %d] Parent continuing...\n", getpid());
        printf("[Parent PID: %d] Parent work completed\n", getpid());
    }

    printf("[PID: %d] Process exiting\n\n", getpid());
    return 0;
}
