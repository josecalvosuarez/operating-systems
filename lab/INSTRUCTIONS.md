# Operating Systems Lab
## Observing Processes and Resource Usage

### Goal
Run simple programs and observe CPU usage, memory usage, and process behavior using Linux monitoring tools.

### Useful Commands

top  
ps -ef  
ps -o pid,ppid,cmd,%cpu,%mem,state  
ps -o pid,ppid,state,cmd  
free -m  
vmstat 1  
pstree -p  
kill <pid>  

Run a program in the background:

./program &

---

# Exercise 1 — CPU Intensive Program

Create the file `cpu_busy.c`.

```c
#include <stdio.h>

int main() {

    volatile unsigned long long x = 0;

    while (1) {
        x++;
    }

    return 0;
}
```

Compile:

```bash
gcc cpu_busy.c -o cpu_busy
```

Run in background:

```bash
./cpu_busy &
```

Observe:

```bash
top
ps -o pid,ppid,%cpu,state,cmd -C cpu_busy
```

---

# Exercise 2 — Memory Growth

Create `mem_grow.c`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHUNK_SIZE (10 * 1024 * 1024)

int main() {

    const int chunks = 10;
    void *blocks[chunks];

    for (int i = 0; i < chunks; i++) {

        blocks[i] = malloc(CHUNK_SIZE);
        memset(blocks[i], 0, CHUNK_SIZE);

        printf("Allocated %d MB\n", (i + 1) * 10);

        sleep(1);
    }

    sleep(20);

    return 0;
}
```

Compile:

```bash
gcc mem_grow.c -o mem_grow
```

Observe memory usage:

```bash
free -m
top
ps -o pid,%mem,rss,vsz,state,cmd -C mem_grow
```

---

# Exercise 3 — fork() Demonstration

Create `fork_demo.c`.

```c
#include <stdio.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        printf("Child PID=%d PPID=%d\n", getpid(), getppid());
        sleep(20);

    } else {

        printf("Parent PID=%d Child=%d\n", getpid(), pid);
        sleep(20);

    }

    return 0;
}
```

Compile:

```bash
gcc fork_demo.c -o fork_demo
```

Observe:

```bash
ps -o pid,ppid,state,cmd -C fork_demo
pstree -p
```

---

# Exercise 4 — Zombie Process

Create `zombie_demo.c`.

```c
#include <stdio.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        printf("Child exiting PID=%d\n", getpid());
        return 0;

    } else {

        printf("Parent sleeping PID=%d Child=%d\n", getpid(), pid);
        sleep(30);

    }

    return 0;
}
```

Compile:

```bash
gcc zombie_demo.c -o zombie_demo
```

Run:

```bash
./zombie_demo
```

Observe zombie processes:

```bash
ps -o pid,ppid,state,cmd | grep zombie_demo
```

Look for process state **Z**.

---

# Exercise 5 — fork() + exec()

Create `exec_demo.c`.

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        printf("Child before exec PID=%d\n", getpid());

        execl("/bin/sleep", "sleep", "10", NULL);

    } else {

        printf("Parent PID=%d Child PID=%d\n", getpid(), pid);

        wait(NULL);

    }

    return 0;
}
```

Compile:

```bash
gcc exec_demo.c -o exec_demo
```

---

# Micro-Experiment — Multiple CPU Loops

Run several CPU loops:

```bash
./cpu_busy &
./cpu_busy &
./cpu_busy &
```

Observe CPU usage:

```bash
top
ps -o pid,%cpu,cmd -C cpu_busy
```

Questions:

- Which program consumed the most CPU?
- What state does a zombie process have?
- How many processes exist after fork()?
- What happens when multiple CPU loops run simultaneously?

---

# Bonus Experiment (Optional)

Observe process state transitions.

Create `sleep_loop.c`.

```c
#include <stdio.h>
#include <unistd.h>

int main() {

    while (1) {

        printf("Working...\n");
        sleep(2);

    }

}
```

Compile:

```bash
gcc sleep_loop.c -o sleep_loop
```

Observe with:

```bash
ps -o pid,state,cmd
top
```

Watch the process alternate between:

R → Running  
S → Sleeping
