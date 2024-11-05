#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace std::chrono;

// Function to read data from a CSV file and store it in a vector
vector<int> readCSV(const string& filename) {
    vector<int> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return data;
    }
    string line, value;
    while (getline(file, line)) {
        stringstream ss(line);
        while (getline(ss, value, ',')) {
            data.push_back(stoi(value));
        }
    }
    file.close();
    return data;
}

// Counting Sort function
void countingSort(vector<int>& arr, int max_value) {
    vector<int> count(max_value + 1, 0);
    for (int num : arr) {
        count[num]++;
    }

    int index = 0;
    for (int i = 0; i <= max_value; ++i) {
        while (count[i]--) {
            arr[index++] = i;
        }
    }
}

// Partition function for Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Radix Sort helper function
void countingSortForRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    for (int num : arr) {
        count[(num / exp) % 10]++;
    }
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

// Radix Sort function
void radixSort(vector<int>& arr) {
    int max_value = *max_element(arr.begin(), arr.end());
    for (int exp = 1; max_value / exp > 0; exp *= 10) {
        countingSortForRadix(arr, exp);
    }
}

int main() {
    const int max_value = 60000;  // Max range of values for Counting Sort

    // Read data from the CSV file
    vector<int> arr = readCSV("input_data.csv");
    if (arr.empty()) {
        cerr << "No data found in CSV file." << endl;
        return 1;
    }

    // Timing Counting Sort
    vector<int> arr1 = arr;
    auto start = high_resolution_clock::now();
    countingSort(arr1, max_value);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Counting Sort time: " << duration.count() << " ms" << endl;

    // Timing Quick Sort
    vector<int> arr2 = arr;
    start = high_resolution_clock::now();
    quickSort(arr2, 0, arr2.size() - 1);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Quick Sort time: " << duration.count() << " ms" << endl;

    // Timing Radix Sort
    vector<int> arr3 = arr;
    start = high_resolution_clock::now();
    radixSort(arr3);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Radix Sort time: " << duration.count() << " ms" << endl;

    return 0;
}
