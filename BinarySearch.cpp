#include <iostream>
#include <vector>
#include <chrono> // For measuring time in nanoseconds
#include <cmath>  // For log2
#include <fstream> // For file operations
#include <sstream> // For string stream operations

// Binary search function
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if target is present at mid
        if (arr[mid] == target)
            return mid;

        // If target is greater, ignore the left half
        if (arr[mid] < target)
            left = mid + 1;

        // If target is smaller, ignore the right half
        else
            right = mid - 1;
    }

    // Target is not present in array
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

        // Parse the "Index" and "Value" columns
        std::getline(ss, index, ',');
        std::getline(ss, value, ',');

        // Convert the value to an integer and store it in the vector
        arr.push_back(std::stoi(value));
    }

    inputFile.close();
    int n = arr.size();
    // Set target value to search for
    int target = -1; // Change target as needed for testing
    const int numTests = 1000000; // Number of tests to average out the time

    // Measure the time taken by binary search in nanoseconds
    auto totalStart = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numTests; ++i) {
        binarySearch(arr, target); // Perform the binary search
    }

    auto totalEnd = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(totalEnd - totalStart); // Total time for numTests
    auto avgTime = elapsed.count() / numTests; // Average time in nanoseconds

    // Perform a final search to see if the element exists
    int index = binarySearch(arr, target);
    if (index != -1) {
        std::cout << "Target found!" << std::endl;
        std::cout << "Index: " << index << std::endl;
        std::cout << "Value: " << arr[index] << std::endl;

        // Compute and display log2(index)
        double logIndex = std::log2(n);
        std::cout << "log2(n): " << logIndex << std::endl;
    } else {
        std::cout << "Target not found in the array." << std::endl;
        double logIndex = std::log2(n);
        std::cout << "log2(n): " << logIndex << std::endl;
    }

    std::cout << "Average Time taken: " << avgTime << " nanoseconds" << std::endl;

    return 0;
}
