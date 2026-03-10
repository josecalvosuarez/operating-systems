/*
 * 02_for_loops.c
 * 
 * TOPIC: For Loops
 * 
 * DESCRIPTION:
 * This program demonstrates different patterns and use cases of for loops
 * in C. For loops are fundamental control structures used for iteration,
 * and understanding them is essential for any C programmer.
 * 
 * LEARNING OBJECTIVES:
 * - Understand for loop syntax and structure
 * - Learn loop initialization, condition, and increment
 * - Explore practical loop patterns (counting, nested loops, etc.)
 * - Understand loop control with break and continue
 * 
 * USAGE:
 *   gcc -o 02_for_loops 02_for_loops.c
 *   ./02_for_loops
 */

#include <stdio.h>

int main(void) {
    int i;  /* Loop counter */

    printf("=== For Loops Demonstration ===\n\n");

    /* --- Example 1: Simple counting loop --- */
    printf("1. Simple counting loop (0 to 9):\n");
    for (i = 0; i < 10; i++) {
        printf("%d ", i);
    }
    printf("\n\n");

    /* --- Example 2: Countdown loop --- */
    printf("2. Countdown loop (10 to 1):\n");
    for (i = 10; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\n\n");

    /* --- Example 3: Loop with step increment (by 2) --- */
    printf("3. Loop with step of 2 (0 to 20):\n");
    for (i = 0; i <= 20; i += 2) {
        printf("%d ", i);
    }
    printf("\n\n");

    /* --- Example 4: Multiplication table --- */
    printf("4. Multiplication table (5 x table):\n");
    for (i = 1; i <= 10; i++) {
        printf("5 x %d = %d\n", i, 5 * i);
    }
    printf("\n");

    /* --- Example 5: Nested for loops (creating a square pattern) --- */
    printf("5. Nested loops (creating a 5x5 star grid):\n");
    int rows = 5;
    int cols = 5;
    for (i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("* ");
        }
        printf("\n");
    }
    printf("\n");

    /* --- Example 6: Nested loops (creating a triangle pattern) --- */
    printf("6. Nested loops (creating a triangle):\n");
    for (i = 1; i <= 5; i++) {
        for (int j = 0; j < i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    printf("\n");

    /* --- Example 7: Loop with break statement --- */
    printf("7. Loop with break (stop when reaching 5):\n");
    for (i = 0; i < 10; i++) {
        if (i == 5) {
            printf("\nReached 5, breaking out of loop\n");
            break;  /* Exit the loop when i equals 5 */
        }
        printf("%d ", i);
    }
    printf("\n\n");

    /* --- Example 8: Loop with continue statement --- */
    printf("8. Loop with continue (skip even numbers):\n");
    for (i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  /* Skip the rest of iteration if i is even */
        }
        printf("%d ", i);
    }
    printf("\n\n");

    /* --- Example 9: Sum calculation using loop --- */
    printf("9. Calculate sum of numbers 1 to 10:\n");
    int sum = 0;
    for (i = 1; i <= 10; i++) {
        sum += i;
    }
    printf("Sum = %d\n", sum);

    return 0;
}
