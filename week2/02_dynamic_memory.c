/*
 * 02_dynamic_memory.c
 * 
 * TOPIC: Dynamic Memory Allocation
 * 
 * DESCRIPTION:
 * This program demonstrates dynamic memory allocation in C using malloc(),
 * calloc(), realloc(), and free(). Dynamic memory allows programs to request
 * memory from the heap at runtime, which is essential for data structures
 * of unknown size.
 * 
 * LEARNING OBJECTIVES:
 * - Understand heap vs. stack memory
 * - Use malloc() to allocate memory
 * - Use calloc() for zero-initialized memory
 * - Use realloc() to resize allocated memory
 * - Use free() to deallocate memory and prevent memory leaks
 * - Understand pointers as references to allocated memory
 * 
 * INCLUDES:
 * - stdlib.h: For malloc(), calloc(), realloc(), free()
 * - stdio.h: For printf()
 * - string.h: For memset()
 * 
 * USAGE:
 *   gcc -o 02_dynamic_memory 02_dynamic_memory.c
 *   ./02_dynamic_memory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    printf("=== Dynamic Memory Allocation Demo ===\n\n");

    /* --- Example 1: Simple malloc allocation --- */
    printf("1. Simple malloc() allocation (for an integer):\n");
    int *ptr_int = malloc(sizeof(int));  /* Allocate memory for one integer */
    
    if (ptr_int == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    *ptr_int = 42;  /* Store value in allocated memory */
    printf("Allocated memory address: %p\n", (void *)ptr_int);
    printf("Value stored: %d\n", *ptr_int);
    free(ptr_int);  /* Always free allocated memory */
    ptr_int = NULL;  /* Good practice: set to NULL after freeing */
    printf("\n");

    /* --- Example 2: Array allocation with malloc --- */
    printf("2. Array allocation with malloc():\n");
    int size = 5;
    int *array = malloc(size * sizeof(int));  /* Allocate array of 5 integers */
    
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    /* Initialize array */
    for (int i = 0; i < size; i++) {
        array[i] = (i + 1) * 10;  /* Store 10, 20, 30, 40, 50 */
    }
    
    printf("Array contents: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    free(array);
    array = NULL;
    printf("\n");

    /* --- Example 3: calloc (allocate and initialize to zero) --- */
    printf("3. calloc() allocation (zero-initialized):\n");
    int *zeros = calloc(5, sizeof(int));  /* Allocate and zero-initialize */
    
    if (zeros == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Array from calloc (should all be 0): ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", zeros[i]);
    }
    printf("\n");
    free(zeros);
    zeros = NULL;
    printf("\n");

    /* --- Example 4: String allocation --- */
    printf("4. String allocation with malloc():\n");
    int string_length = 20;
    char *dynamic_string = malloc(string_length);  /* Allocate for string */
    
    if (dynamic_string == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    strcpy(dynamic_string, "Hello, World!");
    printf("Dynamic string: %s\n", dynamic_string);
    printf("String length: %lu\n", strlen(dynamic_string));
    free(dynamic_string);
    dynamic_string = NULL;
    printf("\n");

    /* --- Example 5: realloc (resize memory) --- */
    printf("5. realloc() to resize allocated memory:\n");
    int *numbers = malloc(3 * sizeof(int));  /* Start with 3 integers */
    
    if (numbers == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 30;
    
    printf("Original array (size 3): ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    /* Resize to 5 integers */
    numbers = realloc(numbers, 5 * sizeof(int));
    if (numbers == NULL) {
        printf("Memory reallocation failed!\n");
        return 1;
    }
    
    /* Initialize new elements */
    numbers[3] = 40;
    numbers[4] = 50;
    
    printf("After realloc (size 5): ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    free(numbers);
    numbers = NULL;
    printf("\n");

    /* --- Example 6: Struct allocation --- */
    printf("6. Dynamic struct allocation:\n");
    
    /* Define a simple struct */
    typedef struct {
        int id;
        char name[50];
        float gpa;
    } Student;
    
    /* Allocate memory for one student */
    Student *student = malloc(sizeof(Student));
    
    if (student == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    /* Initialize struct members */
    student->id = 001;
    strcpy(student->name, "Alice");
    student->gpa = 3.8;
    
    printf("Student ID: %d\n", student->id);
    printf("Student Name: %s\n", student->name);
    printf("Student GPA: %.2f\n", student->gpa);
    free(student);
    student = NULL;
    printf("\n");

    /* --- Example 7: Array of structs --- */
    printf("7. Array of structs:\n");
    int num_students = 3;
    Student *class = malloc(num_students * sizeof(Student));
    
    if (class == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    /* Initialize students */
    strcpy(class[0].name, "Alice");
    class[0].gpa = 3.8;
    
    strcpy(class[1].name, "Bob");
    class[1].gpa = 3.5;
    
    strcpy(class[2].name, "Carol");
    class[2].gpa = 3.9;
    
    /* Display all students */
    for (int i = 0; i < num_students; i++) {
        printf("Student %d: %s (GPA: %.2f)\n", i + 1, class[i].name, class[i].gpa);
    }
    free(class);
    class = NULL;
    printf("\n");

    printf("=== Memory Management Complete ===\n");
    printf("All allocated memory has been freed safely.\n");

    return 0;
}
