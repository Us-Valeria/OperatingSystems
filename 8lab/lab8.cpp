#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void calculateSum(long int& result, int start, int end) {
    result = 0;
    for (int i = start; i <= end; ++i) {
        result += i;
    }
}

int main() {
    const int start = 1;
    const long int end = 1000000;
    int numThreads = 4;

    std::vector<std::thread> threads;

    int chunkSize = (end - start + 1) / numThreads;
    int remainder = (end - start + 1) % numThreads;
    int startIndex = start;
    int endIndex = start + chunkSize - 1;

    auto startTime = std::chrono::steady_clock::now();
    long int totalSum = 0;
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back([&totalSum, startIndex, endIndex]() {
            long int result;
            calculateSum(result, startIndex, endIndex);
            totalSum += result;
        });
        startIndex = endIndex + 1;
        endIndex = startIndex + chunkSize - 1 + (i < remainder ? 1 : 0);
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    auto endTime = std::chrono::steady_clock::now();

    std::cout << "Parallel sum: " << totalSum << std::endl;
    std::cout << "Parallel time: " << std::chrono::duration<double>(endTime - startTime).count() << std::endl;

    return 0;
}