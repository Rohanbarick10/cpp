#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

// Function to generate random numbers and save them to a CSV file
void generateCSV(const string& filename, int n, int max_value) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }
    for (int i = 0; i < n; ++i) {
        file << (rand() % (max_value + 1)) << (i < n - 1 ? "," : "");
    }
    file.close();
    cout << "CSV file " << filename << " created with " << n << " random values." << endl;
}

int main() {
    const int n = 100000;         // Size of the dataset
    const int max_value = 60000;  // Maximum value of random numbers

    generateCSV("input_data.csv", n, max_value);

    return 0;
}
