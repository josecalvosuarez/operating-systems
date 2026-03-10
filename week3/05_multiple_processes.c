/*
 * 05_multiple_processes.c
 * 
 * TOPIC: Managing Multiple Child Processes
 * 
 * DESCRIPTION:
 * This program demonstrates creating and managing multiple child processes.
 * It shows how to fork multiple children, coordinate their execution, and
 * use waitpid() to wait for specific children. This is a more complex example
 * showing realistic process management scenarios.
 * 
 * LEARNING OBJECTIVES:
 * - Create multiple child processes in a loop
 * - Understand process management with multiple children
 * - Use waitpid() to wait for specific processes
 * - Understand parent-child relationships in a tree structure
 * - Handle multiple process events
 * 
 * INCLUDES:
 * - unistd.h: For fork(), getpid(), sleep(), waitpid()
 * - stdio.h: For printf()
 * - stdlib.h: For exit(), malloc()
 * 
 * PROCESS TREE CREATED:
 *        [Parent]
 *          / | \\
 *      [C1] [C2] [C3]  ...
 * 
 * USAGE:
 *   gcc -o 05_multiple_processes 05_multiple_processes.c
 *   ./05_multiple_processes
 *   ./05_multiple_processes 5
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    printf("=== Multiple Child Processes Demo ===\n\n");

    /* Determine number of children to create */
    int num_children = 3;  /* Default */
    if (argc > 1) {
        num_children = atoi(argv[1]);
        if (num_children <= 0) {
            printf("Error: number of children must be positive\n");
            return 1;
        }
    }

    pid_t parent_pid = getpid();
    printf("[Parent PID: %d] Creating %d child processes\n\n", parent_pid, num_children);

    /* Array to store child PIDs */
    pid_t *child_pids = malloc(num_children * sizeof(pid_t));
    if (child_pids == NULL) {
        perror("malloc() failed");
        return 1;
    }

    /* Create multiple children */
    for (int i = 0; i < num_children; i++) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork() failed");
            free(child_pids);
            return 1;
        }

        if (child_pid == 0) {
            /* === CHILD PROCESS === */
            int my_id = i + 1;
            pid_t my_pid = getpid();

            printf("[Child #%d | PID: %d] Child process started\n", my_id, my_pid);
            printf("[Child #%d | PID: %d] Parent PID: %d\n", my_id, my_pid, getppid());

            /* Each child does some work */
            int work_duration = 2 + i;  /* Different duration for each child */
            printf("[Child #%d | PID: %d] Will work for %d seconds\n", my_id, my_pid, work_duration);

            for (int j = 0; j < work_duration; j++) {
                printf("[Child #%d | PID: %d] Working... (%d/%d seconds)\n", 
                       my_id, my_pid, j + 1, work_duration);
                sleep(1);
            }

            printf("[Child #%d | PID: %d] Work complete, exiting with code %d\n", 
                   my_id, my_pid, my_id * 10);
            exit(my_id * 10);  /* Exit with code based on child number */

        } else {
            /* Parent: store child PID and continue */
            child_pids[i] = child_pid;
            printf("[Parent PID: %d] Forked child #%d with PID: %d\n", 
                   parent_pid, i + 1, child_pid);
        }
    }

    printf("\n[Parent PID: %d] All children created. Now waiting for them...\n\n", parent_pid);

    /* === WAIT FOR ALL CHILDREN === */
    int total_status = 0;

    for (int i = 0; i < num_children; i++) {
        int status;
        pid_t completed_pid = waitpid(child_pids[i], &status, 0);

        printf("[Parent PID: %d] Child #%d (PID: %d) has completed\n", 
               parent_pid, i + 1, completed_pid);
        printf("[Parent PID: %d] Child #%d exit status: %d\n", 
               parent_pid, i + 1, status);
        total_status += status;
    }

    printf("\n[Parent PID: %d] All children have completed\n", parent_pid);
    printf("[Parent PID: %d] Combined exit codes: %d\n", parent_pid, total_status);

    /* Clean up */
    free(child_pids);

    printf("[Parent PID: %d] Parent exiting\n\n", parent_pid);
    return 0;
}
