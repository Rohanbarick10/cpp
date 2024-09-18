#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>  // For stringstream to handle CSV parsing
#include <chrono>
#include <cmath>    // For the Fibonacci search
using namespace std;
using namespace std::chrono;

// Struct to store both index and data together
struct IndexedData {
    int index;
    int value;
};

// Function to perform Fibonacci search on the value column
int fibonacciSearch(const vector<IndexedData>& arr, int x) {
    int n = arr.size();
    int fibMm2 = 0;  // (m-2)'th Fibonacci number
    int fibMm1 = 1;  // (m-1)'th Fibonacci number
    int fibM = fibMm1 + fibMm2;  // m'th Fibonacci number

    // Find the smallest Fibonacci number greater than or equal to n
    while (fibM < n) {
        fibMm2 = fibMm1;
        fibMm1 = fibM;
        fibM = fibMm1 + fibMm2;
    }

    int offset = -1;

    // While there are elements to be inspected
    while (fibM > 1) {
        // Calculate the index to be compared
        int i = min(offset + fibMm2, n - 1);

        // If x is greater than the value at index i, cut the subarray from offset to i
        if (arr[i].value < x) {
            fibM = fibMm1;
            fibMm1 = fibMm2;
            fibMm2 = fibM - fibMm1;
            offset = i;
        }
        // If x is less than the value at index i, cut the subarray after i+1
        else if (arr[i].value > x) {
            fibM = fibMm2;
            fibMm1 = fibMm1 - fibMm2;
            fibMm2 = fibM - fibMm1;
        }
        // Element found at index i
        else
            return i;
    }

    // Compare the last element
    if (fibMm1 && offset + 1 < n && arr[offset + 1].value == x)
        return offset + 1;

    // Element not found
    return -1;
}

int main() {
    string fileName;  // The file generated from the previous program
    cout << "Enter the name of the file: ";
    cin >> fileName;

    ifstream inputFile(fileName);

    // Check if the file is opened successfully
    if (!inputFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    vector<IndexedData> arr;
    string line;

    // Skip the header line
    getline(inputFile, line);

    // Read the CSV file line by line
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string indexStr, valueStr;

        // Split by comma
        if (getline(ss, indexStr, ',') && getline(ss, valueStr)) {
            int idx = stoi(indexStr);
            int value = stoi(valueStr);
            arr.push_back({idx, value});
        }
    }

    inputFile.close();

    if (arr.empty()) {
        cerr << "The file is empty or contains no valid data!" << endl;
        return 1;
    }

    int x, numTests;
    // Input the element to search for
    cout << "Enter the element (value) to search: ";
    cin >> x;
    
    // Input the number of tests
    numTests = 100000;

    long long totalTime = 0;  // To store the total time taken for all tests
    int result = -1;  // To store the result of the Fibonacci search

    // Get start time
    auto start = high_resolution_clock::now();

    for (int i = 0; i < numTests; ++i) {
        // Perform Fibonacci search
        result = fibonacciSearch(arr, x);
    }

    // Get end time
    auto stop = high_resolution_clock::now();

    // Calculate duration in nanoseconds
    auto duration = duration_cast<nanoseconds>(stop - start).count();
    
    // Calculate average time
    long long avgTime = duration / numTests;

    // Output the result
    if (result != -1) {
        cout << "Element found at index (file index): " << arr[result].index << " with value: " << arr[result].value << endl;
    } else {
        cout << "Element not found" << endl;
    }

    // Output average time
    cout << "Average time taken by Fibonacci search: " << avgTime << " nanoseconds" << endl;

    return 0;
}
