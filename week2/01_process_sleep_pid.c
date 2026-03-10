/*
 * 01_process_sleep_pid.c
 * 
 * TOPIC: Process Information and Sleep
 * 
 * DESCRIPTION:
 * This program demonstrates how to obtain process information (PID) and
 * use the sleep() function to make a process pause for a specified duration.
 * The program accepts a string argument and a duration, then prints both
 * along with the process ID.
 * 
 * LEARNING OBJECTIVES:
 * - Understand process IDs (PID)
 * - Use getpid() to get current process ID
 * - Use sleep() function for time delays
 * - Process arguments from command line
 * 
 * INCLUDES:
 * - unistd.h: For getpid() and sleep() functions
 * - stdio.h: For standard I/O operations
 * - stdlib.h: For atoi() function
 * 
 * USAGE:
 *   gcc -o 01_process_sleep_pid 01_process_sleep_pid.c
 *   ./01_process_sleep_pid "Hello World" 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  /* For getpid() and sleep() */

int main(int argc, char *argv[]) {
    printf("=== Process Sleep and PID Demo ===\n\n");

    /* Check if arguments are provided */
    if (argc < 2) {
        printf("Usage: %s <string> [sleep_duration_seconds]\n", argv[0]);
        printf("Example: %s \"Hello World\" 3\n", argv[0]);
        return 1;
    }

    /* Get process ID */
    pid_t pid = getpid();
    printf("Process ID (PID): %d\n", pid);
    printf("Message: %s\n", argv[1]);

    /* Determine sleep duration (default: 3 seconds) */
    int sleep_duration = 3;
    if (argc > 2) {
        sleep_duration = atoi(argv[2]);
        if (sleep_duration < 0) {
            printf("Invalid sleep duration. Using default 3 seconds.\n");
            sleep_duration = 3;
        }
    }

    printf("\nStarting to sleep for %d second(s)...\n", sleep_duration);

    /* Loop: print message periodically while "spinning" with sleep */
    printf("\n--- Spinning Process (sleeping in 1-second intervals) ---\n");
    for (int i = 0; i < sleep_duration; i++) {
        printf("[PID %d] Iteration %d of %d: %s\n", pid, i + 1, sleep_duration, argv[1]);
        
        /* Sleep for 1 second */
        sleep(1);
    }

    printf("\n--- Process Complete ---\n");
    printf("Final message from PID %d: %s\n", pid, argv[1]);

    return 0;
}
