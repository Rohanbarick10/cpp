#include <iostream>
#include <vector>
#include <fstream>   // For file handling
#include <sstream>   // For stringstream
#include <cstdlib>   // For rand() function
#include <ctime>     // For seeding rand()
#include <chrono>    // For measuring time

using namespace std;

// Function to merge two subarrays
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// Recursive merge sort
void mergeSortRecursive(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortRecursive(arr, left, mid);
        mergeSortRecursive(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Iterative merge sort
void mergeSortIterative(vector<int>& arr, int n) {
    for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);

            merge(arr, left_start, mid, right_end);
        }
    }
}

int main() {
    
    // Step 1: Read numbers from CSV file
    ifstream infile("input1.csv");
    vector<int> arr1, arr2;
    string line;

    if (!infile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    while (getline(infile, line)) {
        stringstream ss(line);
        string value;
        while (getline(ss, value, ',')) {
            arr1.push_back(stoi(value));
        }
    }

    infile.close();
    arr2 = arr1;  // Copy arr1 to arr2 for the second algorithm

    // Step 2: Sort the data using merge sort
    int size = arr1.size();

    // Measure time for recursive merge sort
    auto start = chrono::high_resolution_clock::now();
    mergeSortRecursive(arr1, 0, size - 1);
    auto end = chrono::high_resolution_clock::now();
    auto recursive_duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Recursive Merge Sort took " << recursive_duration.count() << " milliseconds." << endl;

    // Measure time for iterative merge sort
    start = chrono::high_resolution_clock::now();
    mergeSortIterative(arr2, size);
    end = chrono::high_resolution_clock::now();
    auto iterative_duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Iterative Merge Sort took " << iterative_duration.count() << " milliseconds." << endl;

    // Step 3: Write the sorted data to a new CSV file
    ofstream sortedFile("sorted_output1.csv");

    if (!sortedFile) {
        cerr << "Error creating sorted output file!" << endl;
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        sortedFile << arr1[i];
        if (i != size - 1) {
            sortedFile << ",";
        }
    }

    sortedFile.close();

    // Step 4: Display the sorted data (first 20 numbers for brevity)
    cout << "First 20 sorted numbers:" << endl;
    for (int i = 0; i < 20; ++i) {
        cout << arr1[i] << " ";
    }
    cout << endl;

    return 0;
}
