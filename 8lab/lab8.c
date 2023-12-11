#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

#define NUM_THREADS 4

const long int N = 1000000;

long int result = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* calculateSum(void* threadID) {
    long id = (long)threadID;
    int start = id * N / NUM_THREADS + 1;
    long int end = (id + 1) * N / NUM_THREADS;

    long int localSum = 0;
    for (int i = start; i <= end; ++i) {
        localSum += i;
    }

    pthread_mutex_lock(&mutex);
    result += localSum;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    pthread_t threads[NUM_THREADS];
    int rc;

    for (long i = 0; i < NUM_THREADS; ++i) {
        rc = pthread_create(&threads[i], NULL, calculateSum, (void*)i);
        if (rc) {
            printf("Ошибка; код возврата из pthread_create() - %d\n", rc);
            exit(-1);
        }
    }

    for (long i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL);
    double elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / CLOCKS_PER_SE;

    printf("Parallel sum: %ld\n", result);
    printf("Parallel time: %f seconds\n", elapsedTime);

    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
    return 0;
}
