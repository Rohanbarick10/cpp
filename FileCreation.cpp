#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

int main() {
    // Seed the random number generator
    std::srand(std::time(0));

    std::ofstream outputFile("generated_data.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file!" << std::endl;
        return 1;
    }

    outputFile << "index,value\n"; // Header line

    const int numEntries = 100000; // Number of entries to generate

    for (int i = 0; i < numEntries; ++i) {
        // Generate a random integer value
        int value = i; // Random values between 0 and 999999
        outputFile << i << "," << value << "\n";
    }

    outputFile.close();
    std::cout << "Data generation complete. File: generated_data.csv" << std::endl;

    return 0;
}
