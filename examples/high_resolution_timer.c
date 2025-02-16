#include <time.h>
#include <stdio.h>

int main() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    long long nanoseconds = ts.tv_sec * 1e9 + ts.tv_nsec;
    printf("Current time: %lld nanoseconds since epoch\n", nanoseconds);
    return 0;
}
