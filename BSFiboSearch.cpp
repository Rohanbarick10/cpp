#include <iostream>
#include <vector>
#include <chrono> // For measuring time in nanoseconds
#include <cmath>  // For log2
#include <fstream> // For file operations
#include <sstream> // For string stream operations

// Fibonacci search function
int fibonacciSearch(const std::vector<int>& arr, int target) {
    int n = arr.size();
    int fibM_2 = 0; // (m-2)'th Fibonacci number
    int fibM_1 = 1; // (m-1)'th Fibonacci number
    int fibM = fibM_1 + fibM_2; // m'th Fibonacci number

    while (fibM < n) {
        fibM_2 = fibM_1;
        fibM_1 = fibM;
        fibM = fibM_1 + fibM_2;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = std::min(offset + fibM_2, n - 1);

        if (arr[i] < target) {
            fibM = fibM_1;
            fibM_1 = fibM_2;
            fibM_2 = fibM - fibM_1;
            offset = i;
        } else if (arr[i] > target) {
            fibM = fibM_2;
            fibM_1 = fibM_1 - fibM_2;
            fibM_2 = fibM - fibM_1;
        } else {
            return i;
        }
    }

    if (fibM_1 && arr[offset + 1] == target) {
        return offset + 1;
    }

    return -1;
}

// Binary search function
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int main() {
    // Open input file
    std::ifstream inputFile("generated_data.csv");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> arr;

    // Skip the header line in the CSV file
    std::getline(inputFile, line);

    // Read the input file and store values in the vector
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string index, value;

        std::getline(ss, index, ',');
        std::getline(ss, value, ',');

        arr.push_back(std::stoi(value));
    }

    inputFile.close();

    int n = arr.size(); // Size of the array

    // Set target value to search for
    int target = -1; // Change target as needed for testing

    const int numTests = 100000; // Number of tests to average out the time

    // Measure the time taken by binary search in nanoseconds
    auto binaryTotalStart = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numTests; ++i) {
        binarySearch(arr, target); // Perform the binary search
    }

    auto binaryTotalEnd = std::chrono::high_resolution_clock::now();
    auto binaryElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(binaryTotalEnd - binaryTotalStart);
    auto binaryAvgTime = binaryElapsed.count() / numTests; // Average time in nanoseconds

    // Measure the time taken by Fibonacci search in nanoseconds
    auto fibonacciTotalStart = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numTests; ++i) {
        fibonacciSearch(arr, target); // Perform the Fibonacci search
    }

    auto fibonacciTotalEnd = std::chrono::high_resolution_clock::now();
    auto fibonacciElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(fibonacciTotalEnd - fibonacciTotalStart);
    auto fibonacciAvgTime = fibonacciElapsed.count() / numTests; // Average time in nanoseconds

    // Perform a final search to see if the element exists in both algorithms
    int binaryIndex = binarySearch(arr, target);
    int fibonacciIndex = fibonacciSearch(arr, target);

    // Output results
    if (binaryIndex != -1) {
        std::cout << "Binary Search:" << std::endl;
        std::cout << "Index: " << binaryIndex << std::endl;
        std::cout << "Value: " << arr[binaryIndex] << std::endl;
    } else {
        std::cout << "Binary Search: Target not found in the array." << std::endl;
    }

    if (fibonacciIndex != -1) {
        std::cout << "Fibonacci Search:" << std::endl;
        std::cout << "Index: " << fibonacciIndex << std::endl;
        std::cout << "Value: " << arr[fibonacciIndex] << std::endl;
    } else {
        std::cout << "Fibonacci Search: Target not found in the array." << std::endl;
    }

    std::cout << "Binary Search Average Time: " << binaryAvgTime << " nanoseconds" << std::endl;
    std::cout << "Fibonacci Search Average Time: " << fibonacciAvgTime << " nanoseconds" << std::endl;

    // Output log2(n)
    if (n > 0) {
        double log2n = std::log2(n);
        std::cout << "log2(n): " << log2n << std::endl;
    } else {
        std::cout << "Array size is 0. log2(n) cannot be computed." << std::endl;
    }

    return 0;
}
