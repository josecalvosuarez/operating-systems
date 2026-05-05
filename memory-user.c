#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <MB> [seconds]\n", argv[0]);
        return 1;
    }

    long mb = atol(argv[1]);
    if (mb <= 0) {
        fprintf(stderr, "MB must be a positive integer\n");
        return 1;
    }

    int run_seconds = 0;
    if (argc == 3) {
        run_seconds = atoi(argv[2]);
        if (run_seconds <= 0) {
            fprintf(stderr, "seconds must be a positive integer\n");
            return 1;
        }
    }

    long size = mb * 1024 * 1024 / sizeof(int);
    int *arr = malloc(size * sizeof(int));
    if (!arr) {
        fprintf(stderr, "malloc failed for %ld MB\n", mb);
        return 1;
    }

    printf("Allocated %ld MB, streaming%s...\n",
           mb, run_seconds ? " for a limited time" : " indefinitely");

    time_t start = time(NULL);
    long i = 0;
    while (1) {
        arr[i % size] = i;
        i++;
        if (run_seconds && (i % (size / 4 + 1) == 0)) {
            if (time(NULL) - start >= run_seconds)
                break;
        }
    }

    printf("Done after %ld seconds.\n", (long)(time(NULL) - start));
    free(arr);
    return 0;
}
