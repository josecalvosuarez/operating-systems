/*
 * 01_basic_fork.c
 * 
 * TOPIC: Process Creation with fork()
 * 
 * DESCRIPTION:
 * This program demonstrates the fork() system call, which creates a new
 * process by duplicating the calling process. After fork(), there are two
 * identical processes executing the same code, but with different PIDs.
 * The fork() call returns different values in parent and child to distinguish them.
 * 
 * LEARNING OBJECTIVES:
 * - Understand how fork() creates a new process
 * - Learn the difference between parent and child processes
 * - Understand how fork() return value identifies parent vs child
 * - Learn basic process identifiers (PID, PPID)
 * 
 * INCLUDES:
 * - unistd.h: For fork(), getpid(), sleep()
 * - stdio.h: For printf()
 * - sys/types.h: For pid_t type
 * 
 * PROCESS TREE:
 *                 [Parent Process]
 *                        |
 *                   fork() called
 *                        |
 *          [Parent (continues)] [Child (new process)]
 * 
 * USAGE:
 *   gcc -o 01_basic_fork 01_basic_fork.c
 *   ./01_basic_fork
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    printf("=== Basic fork() Demo ===\n\n");

    pid_t my_pid = getpid();
    printf("[Before fork] Process ID: %d\n\n", my_pid);

    /*
     * fork() system call:
     * - Creates a new process (child) that is a duplicate of calling process (parent)
     * - Child process gets a copy of parent's memory, code, data, etc.
     * - Returns different values in parent and child:
     *   * In parent: returns child's PID (positive)
     *   * In child: returns 0
     *   * On error: returns -1 in parent, child is not created
     */
    pid_t child_pid = fork();

    /* Check if fork() failed */
    if (child_pid == -1) {
        perror("fork() failed");
        return 1;
    }

    /* This code runs in both parent and child processes */
    printf("=== After fork() ===\n");
    printf("Current process ID: %d\n", getpid());

    /* Different code path for parent vs child */
    if (child_pid == 0) {
        /* This is the CHILD process */
        printf("\n[CHILD PROCESS]\n");
        printf("I am the child process!\n");
        printf("My PID: %d\n", getpid());
        printf("My parent's PID: %d\n", getppid());
        printf("---\n");
        
        for (int i = 0; i < 3; i++) {
            printf("[CHILD] Working... iteration %d\n", i + 1);
            sleep(1);  /* Sleep for 1 second */
        }
        
        printf("[CHILD] Done!\n");
        return 0;  /* Child process exits here */

    } else {
        /* This is the PARENT process */
        printf("\n[PARENT PROCESS]\n");
        printf("I am the parent process!\n");
        printf("My PID: %d\n", getpid());
        printf("My child's PID: %d\n", child_pid);
        printf("---\n");
        
        for (int i = 0; i < 3; i++) {
            printf("[PARENT] Working... iteration %d\n", i + 1);
            sleep(1);  /* Sleep for 1 second */
        }
        
        printf("[PARENT] Done!\n");
    }

    printf("\n[%d] Process exiting\n", getpid());
    return 0;
}
