#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>  // For stringstream to handle CSV parsing
#include <chrono>
using namespace std;
using namespace std::chrono;

// Struct to store both index and data together
struct IndexedData {
    int index;
    int value;
};

// Function for binary search on the value column
int binarySearch(const vector<IndexedData>& arr, int left, int right, int x) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if x is present at mid
        if (arr[mid].value == x)
            return mid;

        // If x greater, ignore left half
        if (arr[mid].value < x)
            left = mid + 1;

        // If x is smaller, ignore right half
        else
            right = mid - 1;
    }

    // Element is not present in array
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

    // Check if data was successfully read
    int numEntries = arr.size();
    if (numEntries == 0) {
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
    int result = -1;  // To store the result of the binary search

    // Get start time
    auto start = high_resolution_clock::now();

    for (int i = 0; i < numTests; ++i) {
        // Perform binary search
        result = binarySearch(arr, 0, arr.size() - 1, x);
    }

    // Get end time
    auto stop = high_resolution_clock::now();

    // Calculate duration in nanoseconds
    auto duration = duration_cast<nanoseconds>(stop - start).count();
    // Calculate average time
    long long avgTime = duration / numTests;

    // Output the result of the search
    if (result != -1) {
        cout << "Element found at index (file index): " << arr[result].index << " with value: " << arr[result].value << endl;
    } else {
        cout << "Element not found" << endl;
    }

    // Output the average time taken and number of entries
    cout << "Binary search performed on " << numEntries << " entries." << endl;
    cout << "Average time taken by binary search: " << avgTime << " nanoseconds" << endl;

    return 0;
}
