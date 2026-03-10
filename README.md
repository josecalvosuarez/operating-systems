# Operating Systems Course - Code Examples

A comprehensive collection of C programming examples for an undergraduate Operating Systems course. These examples progress incrementally from basic C concepts through advanced process management.

## Project Structure

```
operating-systems/
├── week1/                    # Fundamentals of C programming
│   ├── 01_command_line_args.c
│   ├── 02_for_loops.c
│   └── 03_string_operations.c
├── week2/                    # Process basics and system calls
│   ├── 01_process_sleep_pid.c
│   ├── 02_dynamic_memory.c
│   └── 03_file_io_syscalls.c
└── week3/                    # Process creation and management
    ├── 01_basic_fork.c
    ├── 02_fork_with_wait.c
    ├── 03_fork_exec_basic.c
    ├── 04_fork_exec_with_args.c
    └── 05_multiple_processes.c
```

---

## Week 1: C Programming Fundamentals

### 01_command_line_args.c
**Topic:** Command-line argument processing

**Key Concepts:**
- `argc` (argument count) and `argv` (argument vector)
- Accessing command-line arguments
- Converting arguments to different data types

**Compilation:**
```bash
gcc -o 01_command_line_args 01_command_line_args.c
```

**Usage Examples:**
```bash
./01_command_line_args hello world 42
./01_command_line_args "Single Argument"
```

**Learning Outcomes:**
- Understand how programs receive input from the shell
- Learn to parse and process command-line arguments

---

### 02_for_loops.c
**Topic:** For loop patterns and control flow

**Key Concepts:**
- Loop initialization, condition, increment
- Nested loops
- Loop control with `break` and `continue`
- Common loop patterns

**Compilation:**
```bash
gcc -o 02_for_loops 02_for_loops.c
```

**Usage:**
```bash
./02_for_loops
```

**Examples Included:**
- Simple counting (0 to 9)
- Countdown loops
- Step increments
- Multiplication tables
- Nested loops (creating patterns)
- Loop with break/continue
- Summation

---

### 03_string_operations.c
**Topic:** String manipulation and built-in functions

**Key Concepts:**
- String representation in C (character arrays)
- `strlen()` - get string length
- `strcpy()` - copy strings
- `strcat()` - concatenate strings
- `strcmp()` - compare strings
- `strchr()` - find character in string
- Manual string traversal

**Compilation:**
```bash
gcc -o 03_string_operations 03_string_operations.c
```

**Usage:**
```bash
./03_string_operations
```

**Important Note:** The examples use `strcpy()` for educational purposes. In production code, use safer alternatives like `strncpy()` or `strlcpy()`.

---

## Week 2: System Calls and Process Basics

### 01_process_sleep_pid.c
**Topic:** Process identification and time delays

**Key Concepts:**
- `getpid()` - get process ID
- `sleep()` - pause process execution
- Process Information display

**System Calls Used:**
- `getpid()`
- `sleep()`

**Compilation:**
```bash
gcc -o 01_process_sleep_pid 01_process_sleep_pid.c
```

**Usage Examples:**
```bash
./01_process_sleep_pid "Hello World" 3
./01_process_sleep_pid "Processing" 5
```

**Learning Outcomes:**
- Understand process IDs as process identifiers
- Learn time-based process control
- See concurrent (but independent) process execution

---

### 02_dynamic_memory.c
**Topic:** Dynamic memory allocation and management

**Key Concepts:**
- Heap vs. stack memory
- `malloc()` - allocate memory
- `calloc()` - allocate and zero-initialize
- `realloc()` - resize allocated memory
- `free()` - deallocate memory
- Memory leak prevention
- Pointers and dynamic data structures

**Compilation:**
```bash
gcc -o 02_dynamic_memory 02_dynamic_memory.c
```

**Usage:**
```bash
./02_dynamic_memory
```

**Examples Included:**
1. Single integer allocation
2. Array allocation and initialization
3. Calloc with zero-initialization
4. String allocation
5. Memory reallocation
6. Dynamic struct allocation
7. Array of structs

**Learning Outcomes:**
- Understand memory management in C
- Learn to work with pointers
- Implement data structures with dynamic sizing

---

### 03_file_io_syscalls.c
**Topic:** Low-level file I/O using system calls

**Key Concepts:**
- File descriptors (FDs)
- `open()` - open or create files
- `write()` - write data to files
- `read()` - read data from files
- `close()` - close file descriptors
- File flags: `O_CREAT`, `O_WRONLY`, `O_TRUNC`, `O_RDONLY`
- File permissions (octal notation)
- Error handling

**System Calls Used:**
- `open()`
- `write()`
- `read()`
- `close()`

**Compilation:**
```bash
gcc -o 03_file_io_syscalls 03_file_io_syscalls.c
```

**Usage Examples:**
```bash
./03_file_io_syscalls myfile.txt "Hello from system calls!"
./03_file_io_syscalls test.txt "Multiple lines of data"
./03_file_io_syscalls output.log "Important log message"
```

**File Flag Reference:**
- `O_CREAT` - Create file if it doesn't exist
- `O_WRONLY` - Open for writing only
- `O_RDONLY` - Open for reading only
- `O_TRUNC` - Truncate file to zero size
- `O_APPEND` - Append to end of file

**Permission Reference:**
- `0644` = rw-r--r-- (owner read/write, others read)
- `0755` = rwxr-xr-x (owner all, others read/execute)

**Learning Outcomes:**
- Understand difference between system calls and library functions
- Learn low-level file I/O operations
- Understand file descriptors and their role
- Practice error handling with system calls

---

## Week 3: Process Creation and Management

### 01_basic_fork.c
**Topic:** Creating child processes with `fork()`

**Key Concepts:**
- `fork()` - create a new process
- Parent vs. child process execution
- Process duplication
- Fork return values
- Process IDs (PID) and parent IDs (PPID)

**System Calls Used:**
- `fork()`
- `getpid()`
- `getppid()`

**Compilation:**
```bash
gcc -o 01_basic_fork 01_basic_fork.c
```

**Usage:**
```bash
./01_basic_fork
```

**Fork Mechanics:**
- Returns 0 in child process
- Returns child's PID in parent process
- Returns -1 on error (child not created in parent only)

**Learning Outcomes:**
- Understand how operating systems create new processes
- Learn process hierarchy
- See concurrent execution of parent and child

---

### 02_fork_with_wait.c
**Topic:** Process synchronization with `wait()`

**Key Concepts:**
- `wait()` - wait for child process termination
- Parent blocking and child completion
- Zombie process prevention
- Exit status codes
- `WIFEXITED()` macro
- `WEXITSTATUS()` macro

**System Calls Used:**
- `fork()`
- `wait()`
- `exit()`

**Compilation:**
```bash
gcc -o 02_fork_with_wait 02_fork_with_wait.c
```

**Usage:**
```bash
./02_fork_with_wait
```

**Exit Status:**
- Parent can retrieve child's exit code (0-255)
- Use `WIFEXITED()` to check normal exit
- Use `WEXITSTATUS()` to get the exit code

**Learning Outcomes:**
- Understand process synchronization
- Learn to coordinate parent-child execution
- Prevent zombie processes
- Retrieve and interpret exit status codes

---

### 03_fork_exec_basic.c
**Topic:** Executing external programs with `exec()`

**Key Concepts:**
- `exec()` family of functions
- Process image replacement
- `execlp()` - list arguments with PATH search
- Command execution
- File descriptor inheritance

**System Calls Used:**
- `fork()`
- `execlp()` (and related exec functions)
- `wait()`

**Compilation:**
```bash
gcc -o 03_fork_exec_basic 03_fork_exec_basic.c
```

**Usage:**
```bash
./03_fork_exec_basic
```

**Exec Variants:**
- `execl(path, arg0, arg1, ..., NULL)` - with full path
- `execlp(prog, arg0, arg1, ..., NULL)` - searches PATH
- `execv(path, argv[])` - use argument array, full path
- `execvp(prog, argv[])` - use array, searches PATH

**Important:** Code after `exec()` only runs if `exec()` fails!

**Learning Outcomes:**
- Understand program execution model
- Learn how shells execute commands
- See replacement of process image
- Understand fork-exec pattern

---

### 04_fork_exec_with_args.c
**Topic:** Passing arguments to executed programs

**Key Concepts:**
- Argument array construction
- `execvp()` with argument vectors
- Dynamic argument passing
- Real-world command execution
- Program invocation flexibly

**System Calls Used:**
- `fork()`
- `execvp()`
- `wait()`
- `waitpid()` with specific PIDs

**Compilation:**
```bash
gcc -o 04_fork_exec_with_args 04_fork_exec_with_args.c
```

**Usage Examples:**
```bash
./04_fork_exec_with_args echo Hello World
./04_fork_exec_with_args cat /etc/hostname
./04_fork_exec_with_args grep main 04_fork_exec_with_args.c
./04_fork_exec_with_args ls -la /tmp
```

**Argument Array Construction:**
- `argv[0]` = program name
- `argv[1..n]` = arguments
- `argv[n+1]` = NULL (required terminator)

**Learning Outcomes:**
- Learn practical program execution
- Understand argument passing mechanisms
- Build custom command shells behavior
- Practice pointer arrays and dynamic allocation

---

### 05_multiple_processes.c
**Topic:** Managing multiple simultaneous processes

**Key Concepts:**
- Creating multiple child processes
- Process tree structure
- `waitpid()` for specific process waiting
- Handling multiple process exits
- Process synchronization at scale

**System Calls Used:**
- `fork()`
- `waitpid()`
- `exit()`

**Compilation:**
```bash
gcc -o 05_multiple_processes 05_multiple_processes.c
```

**Usage Examples:**
```bash
./05_multiple_processes          # Creates 3 children (default)
./05_multiple_processes 5        # Creates 5 children
./05_multiple_processes 10       # Creates 10 children
```

**Process Tree Example:**
```
        [Parent]
        /  |  \
      C1   C2  C3
```

**Key Features:**
- Dynamic number of children based on argument
- Different work duration for each child
- Waits for each child specifically using `waitpid()`
- Accumulates exit codes

**Learning Outcomes:**
- Scale process management to real scenarios
- Coordinate multiple concurrent processes
- Understand process synchronization patterns
- Learn advanced process hierarchy management

---

## Compilation and Execution Guide

### Quick Compilation
```bash
# Compile all Week 1 examples
cd week1
gcc -o 01_command_line_args 01_command_line_args.c
gcc -o 02_for_loops 02_for_loops.c
gcc -o 03_string_operations 03_string_operations.c

# Compile all Week 2 examples
cd ../week2
gcc -o 01_process_sleep_pid 01_process_sleep_pid.c
gcc -o 02_dynamic_memory 02_dynamic_memory.c
gcc -o 03_file_io_syscalls 03_file_io_syscalls.c

# Compile all Week 3 examples
cd ../week3
gcc -o 01_basic_fork 01_basic_fork.c
gcc -o 02_fork_with_wait 02_fork_with_wait.c
gcc -o 03_fork_exec_basic 03_fork_exec_basic.c
gcc -o 04_fork_exec_with_args 04_fork_exec_with_args.c
gcc -o 05_multiple_processes 05_multiple_processes.c
```

### Batch Compilation Script
Create `compile_all.sh`:
```bash
#!/bin/bash

for dir in week1 week2 week3; do
    echo "Compiling $dir..."
    cd $dir
    for file in *.c; do
        if [ -f "$file" ]; then
            binary="${file%.c}"
            gcc -o "$binary" "$file"
            echo "  Compiled: $binary"
        fi
    done
    cd ..
done

echo "All compilations complete!"
```

Then run:
```bash
chmod +x compile_all.sh
./compile_all.sh
```

---

## Learning Path Recommendations

### For Beginners
1. Start with **Week 1** to refresh C fundamentals
2. Progress to **Week 2** to understand system interaction
3. Conclude with **Week 3** for process management

### Sequential Topic Study
1. **Memory & I/O**: Week 2 (02, 03) before Week 3
2. **Process Basics**: Week 3 (01, 02) before exec examples
3. **Program Execution**: Week 3 (03, 04) together
4. **Advanced**: Week 3 (05) after understanding fork/exec

### Hands-On Exercises

#### After Week 1
- Modify `01_command_line_args.c` to multiply three numbers
- Enhance `02_for_loops.c` to create different patterns
- Add case conversion to `03_string_operations.c`

#### After Week 2
- Extend `01_process_sleep_pid.c` with multiple messages
- Implement a linked list in `02_dynamic_memory.c`
- Add error handling to `03_file_io_syscalls.c`

#### After Week 3
- Create a process pool with `05_multiple_processes.c`
- Build a simple shell with fork/exec examples
- Implement process communication with pipes

---

## Important System-Specific Notes

### macOS
- Use `man` for system call documentation: `man 2 fork`
- Some paths may differ (e.g., `/usr/bin/ls` instead of `/bin/ls`)
- Performance characteristics may vary due to Darwin kernel

### Linux
- System calls generally match POSIX standards
- Use `man` pages: `man 2 fork`
- Watch for zombie process signals

### General Notes
- Always compile with: `gcc -o output_name source.c`
- Test with various arguments to understand behavior
- Use `ps` command to monitor running processes
- Use `strace` (Linux) or `dtrace` (macOS) to trace system calls

---

## Debugging Tips

### Running with Debug Information
```bash
gcc -g -o program_name program.c
gdb ./program_name
```

### Tracing System Calls
**Linux:**
```bash
strace ./program_name [args]
```

**macOS:**
```bash
dtrace -n 'syscall:::entry { @[execname] = count(); }' -c './program_name [args]'
```

### Checking Running Processes
```bash
ps aux | grep program_name
ps -e -o pid,ppid,cmd | grep program_name
```

### Monitoring File Operations
```bash
lsof -p <pid>
```

---

## Common Compilation Warnings and Solutions

### Warning: implicit function declaration
**Problem:** Using function without including proper header
```
warning: implicit declaration of function 'fork' [-Wimplicit-function-declaration]
```
**Solution:** Include `#include <unistd.h>` for fork, exec, etc.

### Warning: comparison with string literal
**Problem:** Using `==` to compare strings
```
warning: comparison with string literal is unspecified [-Wconstant-conversion]
```
**Solution:** Use `strcmp()` instead of `==`

### Compile with Strict Warnings
```bash
gcc -Wall -Wextra -o program_name program.c
```

---

## Key System Calls Reference

| Call | Return | Purpose |
|------|--------|---------|
| `fork()` | PID or 0 | Create child process |
| `wait()` | PID | Wait for child, get status |
| `waitpid()` | PID | Wait for specific child |
| `exec*()` | -1 | Replace process image |
| `exit()` | N/A | Terminate process |
| `getpid()` | PID | Get process ID |
| `open()` | FD | Open/create file |
| `read()` | bytes | Read from FD |
| `write()` | bytes | Write to FD |
| `close()` | 0|-1 | Close FD |
| `sleep()` | 0 | Pause execution |

---

## Additional Resources

### Man Pages
- System calls: `man 2 <function>`
- C library: `man 3 <function>`
- General topics: `man 7 <topic>`

### Online Learning
- POSIX.1-2017 standards
- Linux man pages online: man7.org
- C Programming Language (K&R) textbook reference

### Practice Suggestions
1. Modify examples to add new functionality
2. Combine concepts from different examples
3. Create simple shell implementing fork/exec
4. Build process monitoring utility

---

## License and Academic Use

These examples are provided for educational purposes. Feel free to:
- Modify code for learning
- Share with students and colleagues
- Use as basis for assignments
- Reference in teaching materials

Please maintain educational integrity - students should understand code they submit!

---

**Last Updated:** March 2026
**Difficulty Levels:** Beginner (Week 1) → Intermediate (Week 2) → Advanced (Week 3)
