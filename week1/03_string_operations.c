/*
 * 03_string_operations.c
 * 
 * TOPIC: String Operations
 * 
 * DESCRIPTION:
 * This program demonstrates fundamental string operations in C.
 * Strings in C are arrays of characters terminated by a null character ('\0').
 * This example covers common operations like length, copying, concatenation,
 * and comparison.
 * 
 * LEARNING OBJECTIVES:
 * - Understand C string representation
 * - Learn built-in string functions (strlen, strcpy, strcat, strcmp)
 * - Understand safe string operations
 * - Practice string manipulation
 * 
 * USAGE:
 *   gcc -o 03_string_operations 03_string_operations.c
 *   ./03_string_operations
 */

#include <stdio.h>
#include <string.h>  /* For string functions */

int main(void) {
    printf("=== String Operations Demonstration ===\n\n");

    /* --- Example 1: String Declaration and Initialization --- */
    printf("1. String Declaration and Initialization:\n");
    char greeting[] = "Hello, World!";  /* Array initialization */
    char name[50];  /* Buffer for user string */
    
    printf("String: %s\n\n", greeting);

    /* --- Example 2: String Length (strlen) --- */
    printf("2. String Length using strlen():\n");
    int length = strlen(greeting);
    printf("Length of \"%s\": %d characters\n\n", greeting, length);

    /* --- Example 3: Accessing individual characters --- */
    printf("3. Individual Characters:\n");
    printf("Characters in '%s':\n", greeting);
    for (int i = 0; i < strlen(greeting); i++) {
        printf("  Index %d: '%c'\n", i, greeting[i]);
    }
    printf("\n");

    /* --- Example 4: String Copy (strcpy - note: not bounds-safe) --- */
    printf("4. String Copy using strcpy():\n");
    strcpy(name, "Alice");
    printf("Original: %s\n", greeting);
    printf("Copied name: %s\n", name);
    printf("These are different strings in memory\n\n");

    /* --- Example 5: String Concatenation (strcat) --- */
    printf("5. String Concatenation using strcat():\n");
    char str1[100] = "Hello";
    char str2[100] = " Operating Systems";
    strcat(str1, str2);
    printf("Result: %s\n\n", str1);

    /* --- Example 6: String Comparison (strcmp) --- */
    printf("6. String Comparison using strcmp():\n");
    char word1[] = "apple";
    char word2[] = "apple";
    char word3[] = "banana";
    
    /* strcmp returns 0 if strings are equal, negative if first < second, positive otherwise */
    int result1 = strcmp(word1, word2);
    int result2 = strcmp(word1, word3);
    
    printf("strcmp(\"%s\", \"%s\") = %d (0 means equal)\n", word1, word2, result1);
    printf("strcmp(\"%s\", \"%s\") = %d\n", word1, word3, result2);
    printf("\n");

    /* --- Example 7: Finding character in string (strchr) --- */
    printf("7. Finding character in string using strchr():\n");
    char text[] = "Operating Systems";
    char *position = strchr(text, 'S');
    if (position != NULL) {
        printf("Found 'S' at position %ld in \"%s\"\n", position - text, text);
    }
    printf("\n");

    /* --- Example 8: Manual string traversal --- */
    printf("8. Manual String Traversal:\n");
    char str[] = "Code";
    printf("String: %s\n", str);
    printf("Character by character:\n");
    
    for (int i = 0; str[i] != '\0'; i++) {  /* Loop until null terminator */
        printf("  str[%d] = '%c'\n", i, str[i]);
    }
    printf("\n");

    /* --- Example 9: String case operations (simple) --- */
    printf("9. Converting to uppercase (manual):\n");
    char original[] = "hello";
    char uppercase[50];
    strcpy(uppercase, original);
    
    printf("Original: %s\n", original);
    printf("Uppercase: ");
    for (int i = 0; uppercase[i] != '\0'; i++) {
        if (uppercase[i] >= 'a' && uppercase[i] <= 'z') {
            uppercase[i] = uppercase[i] - 'a' + 'A';  /* Convert lowercase to uppercase */
        }
        printf("%c", uppercase[i]);
    }
    printf("\n\n");

    /* --- Example 10: String comparison with conditional --- */
    printf("10. Practical String Comparison:\n");
    char password[] = "secret123";
    char input[] = "secret123";
    
    if (strcmp(password, input) == 0) {
        printf("Passwords match!\n");
    } else {
        printf("Passwords do not match!\n");
    }

    return 0;
}
