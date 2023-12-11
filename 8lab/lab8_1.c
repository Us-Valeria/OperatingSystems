#include <stdio.h>
#include <time.h>

void calculateSum(int start, int end, long int* result) {
    for (int i = start; i <= end; ++i) {
        *result += i;
    }
}

int main() {
    const int start = 1;
    const long int end = 10000000;
    
    long int sequentialSum = 0;
    clock_t startSequential = clock();

    calculateSum(start, end, &sequentialSum);

    clock_t endSequential = clock();
    double sequentialTime = (double)(endSequential - startSequential) / CLOCKS_PER_SEC;

    printf("Sequential sum: %ld\n", sequentialSum);
    printf("Sequential time: %f seconds\n", sequentialTime);

    return 0;
}