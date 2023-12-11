#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <sys/time.h>

#define N 10000000
#define NUM_THREADS 4

atomic_long result = 0;

void* calculateSum(void* threadID) {
    long id = (long)threadID;
    int start = id * N / NUM_THREADS + 1;
    long end = (id + 1) * N / NUM_THREADS;

    long localSum = 0;

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = start; i <= end; ++i) {
        localSum += i;
    }

    gettimeofday(&end_time, NULL);

    atomic_fetch_add(&result, localSum);

    long long execution_time = (end_time.tv_sec - start_time.tv_sec) * 1000000LL + end_time.tv_usec - start_time.tv_usec;
    printf("Thread %ld computation time: %lld microseconds\n", id, execution_time);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, calculateSum, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);
    long long total_execution_time = (end_time.tv_sec - start_time.tv_sec) * 1000000LL + end_time.tv_usec - start_time.tv_usec;
    printf("Total computation time for all threads: %lld microseconds\n", total_execution_time);
    printf("Result: %ld\n", atomic_load(&result));

    return 0;
}