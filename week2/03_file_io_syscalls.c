/*
 * 03_file_io_syscalls.c
 * 
 * TOPIC: File I/O Using System Calls
 * 
 * DESCRIPTION:
 * This program demonstrates low-level file I/O operations using POSIX
 * system calls: open(), write(), read(), and close(). System calls provide
 * direct access to the operating system's file handling capabilities, unlike
 * higher-level C library functions (fopen, fprintf).
 * 
 * LEARNING OBJECTIVES:
 * - Understand file descriptors
 * - Use open() to create/open files with specific flags and permissions
 * - Use write() to write data to files
 * - Use read() to read data from files
 * - Handle file I/O errors
 * - Understand file permissions and flags
 * 
 * INCLUDES:
 * - unistd.h: For open(), write(), read(), close()
 * - fcntl.h: For open() flags (O_CREAT, O_WRONLY, etc.)
 * - sys/stat.h: For file permission constants
 * - stdio.h: For printf()
 * - string.h: For strlen()
 * - stdlib.h: For exit()
 * 
 * USAGE:
 *   gcc -o 03_file_io_syscalls 03_file_io_syscalls.c
 *   ./03_file_io_syscalls myfile.txt "Hello from system calls!"
 *   ./03_file_io_syscalls test.txt "Multiple lines of data"
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      /* For open(), write(), read(), close() */
#include <fcntl.h>       /* For open() flags */
#include <sys/stat.h>    /* For file permissions */
#include <string.h>      /* For strlen() */

int main(int argc, char *argv[]) {
    printf("=== File I/O Using System Calls Demo ===\n\n");

    /* Check command line arguments */
    if (argc < 3) {
        printf("Usage: %s <filename> <message>\n", argv[0]);
        printf("Example: %s myfile.txt \"Hello World\"\n", argv[0]);
        printf("\nThis program creates/overwrites a file and writes a message to it.\n");
        return 1;
    }

    char *filename = argv[1];
    char *message = argv[2];

    printf("Filename: %s\n", filename);
    printf("Message: %s\n", message);
    printf("\n--- Opening file for writing ---\n");

    /*
     * open() system call parameters:
     * - filename: path to file
     * - flags: control how file is opened
     *   * O_CREAT: create file if it doesn't exist
     *   * O_WRONLY: open for writing only
     *   * O_TRUNC: truncate file to zero size if it exists
     * - mode: file permissions (in octal)
     *   * 0644: rw-r--r-- (owner can read/write, others can read)
     */
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    /* Check if open() succeeded */
    if (fd == -1) {
        perror("Error opening file");  /* Print system error message */
        return 1;
    }

    printf("File opened successfully. File descriptor: %d\n", fd);

    /* --- Writing to file --- */
    printf("\n--- Writing to file ---\n");
    
    /* Calculate message length */
    size_t message_length = strlen(message);
    printf("Message length: %zu bytes\n", message_length);

    /*
     * write() system call parameters:
     * - fd: file descriptor returned by open()
     * - buffer: pointer to data to write
     * - count: number of bytes to write
     * Returns: number of bytes actually written, or -1 on error
     */
    ssize_t bytes_written = write(fd, message, message_length);

    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    printf("Bytes written: %ld/%zu\n", bytes_written, message_length);

    /* --- Writing a newline for readability --- */
    printf("\n--- Writing additional content ---\n");
    const char *newline = "\n";
    write(fd, newline, strlen(newline));
    printf("Added newline to file.\n");

    /* --- Writing formatted content with buffer --- */
    printf("\n--- Writing metadata ---\n");
    
    char buffer[256];  /* Buffer for formatted content */
    int bytes_formatted = snprintf(buffer, sizeof(buffer),
                                   "File: %s | Length: %zu bytes | PID: %d\n",
                                   filename, message_length, getpid());
    
    if (bytes_formatted > 0) {
        ssize_t meta_written = write(fd, buffer, bytes_formatted);
        if (meta_written == -1) {
            perror("Error writing metadata");
            close(fd);
            return 1;
        }
        printf("Metadata written: %ld bytes\n", meta_written);
    }

    /* --- Close the file --- */
    printf("\n--- Closing file ---\n");
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }
    printf("File closed successfully.\n");

    /* --- Demonstrate reading the file back --- */
    printf("\n--- Reading file back ---\n");
    printf("Contents of %s:\n", filename);
    printf("--- BEGIN FILE ---\n");

    /* Open file for reading */
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }

    /* Read file in chunks */
    char read_buffer[1024];
    ssize_t bytes_read;
    
    while ((bytes_read = read(fd, read_buffer, sizeof(read_buffer))) > 0) {
        /* Write directly to stdout (file descriptor 1) */
        write(STDOUT_FILENO, read_buffer, bytes_read);
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        return 1;
    }

    printf("--- END FILE ---\n");

    /* Close file */
    close(fd);

    printf("\n=== File I/O Demo Complete ===\n");

    return 0;
}
