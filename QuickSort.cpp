#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <chrono>

// Function to read integers from a CSV file
std::vector<int> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<int> data;
    std::string line, value;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream ss(line);
            while (getline(ss, value, ',')) {
                data.push_back(std::stoi(value));  // Convert string to integer
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
    return data;
}

// Function to write integers to a CSV file
void writeCSV(const std::string& filename, const std::vector<int>& data) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (size_t i = 0; i < data.size(); ++i) {
            file << data[i];
            if (i < data.size() - 1) {
                file << ",";  // Add comma between values
            }
        }
        file.close();
        std::cout << "Data written to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}

// Standard Quicksort using the first element as pivot
void quicksortFixedPivot(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivot = arr[left];  // Fixed pivot (first element)
        int i = left;
        int j = right;

        while (i < j) {
            while (arr[i] <= pivot && i < right) i++;
            while (arr[j] > pivot) j--;
            if (i < j) std::swap(arr[i], arr[j]);
        }
        std::swap(arr[left], arr[j]);

        quicksortFixedPivot(arr, left, j - 1);
        quicksortFixedPivot(arr, j + 1, right);
    }
}

// Quicksort using a random pivot
void quicksortRandomPivot(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivotIndex = left + rand() % (right - left + 1);  // Random pivot
        int pivot = arr[pivotIndex];
        std::swap(arr[left], arr[pivotIndex]);  // Move pivot to the start
        int i = left;
        int j = right;

        while (i < j) {
            while (arr[i] <= pivot && i < right) i++;
            while (arr[j] > pivot) j--;
            if (i < j) std::swap(arr[i], arr[j]);
        }
        std::swap(arr[left], arr[j]);

        quicksortRandomPivot(arr, left, j - 1);
        quicksortRandomPivot(arr, j + 1, right);
    }
}

// Function to print the first N elements of a sorted array
void printArray(const std::vector<int>& arr, int N ) {
    int size = arr.size() < N ? arr.size() : N;
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << (i == size - 1 ? "\n" : ", ");
    }
}

int main() {
    std::string filename = "input2.csv";  // Rename as per the FileName
    std::vector<int> data = readCSV(filename);
    
    if (data.empty()) {
        std::cerr << "No data read from the file." << std::endl;
        return 1;
    }

    // Copy data for the two versions of Quicksort
    std::vector<int> dataFixed = data;
    std::vector<int> dataRandom = data;

    // Measure time for Quicksort with fixed pivot
    auto startFixed = std::chrono::high_resolution_clock::now();
    quicksortFixedPivot(dataFixed, 0, dataFixed.size() - 1);
    auto endFixed = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationFixed = endFixed - startFixed;

    // Measure time for Quicksort with random pivot
    auto startRandom = std::chrono::high_resolution_clock::now();
    quicksortRandomPivot(dataRandom, 0, dataRandom.size() - 1);
    auto endRandom = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationRandom = endRandom - startRandom;

    // Output time results
    std::cout << "Quicksort with fixed pivot took: " << durationFixed.count() << " seconds." << std::endl;
    std::cout << "Sorted values (fixed pivot): ";
    printArray(dataFixed, 20);  // Print first 10 sorted values

    std::cout << "Quicksort with random pivot took: " << durationRandom.count() << " seconds." << std::endl;
    std::cout << "Sorted values (random pivot): ";
    printArray(dataRandom, 20);  // Print first 10 sorted values

    // Write sorted arrays to CSV files
    writeCSV("sorted2.csv", dataFixed);

    return 0;
}
