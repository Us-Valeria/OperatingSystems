#include <iostream>
#include <chrono>
#include <vector>
#include <thread>

void calculateSum(int start, int end, long int& result) {
    result = 0; 
    for (int i = start; i <= end; ++i) {
        result += i;
    }
}

int main() {
    const int start = 1;
    const long int end = 1000000;
    
    long int sequentialSum = 0;
    std::chrono::steady_clock::time_point startSequential = std::chrono::steady_clock::now();

    calculateSum(start, end, sequentialSum);

    std::chrono::steady_clock::time_point endSequential = std::chrono::steady_clock::now();
    std::chrono::duration<double> sequentialTime = std::chrono::duration_cast<std::chrono::duration<double>>(endSequential - startSequential);

    std::cout << "Sequential sum: " << sequentialSum << std::endl;
    std::cout << "Sequential time: " << sequentialTime.count() << " seconds" << std::endl;

    return 0;
}