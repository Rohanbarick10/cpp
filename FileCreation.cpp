#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ofstream outputFile("generated_data.csv"); // can be renamed as per requirements
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file!" << std::endl;
        return 1;
    }

    outputFile << "index,value\n"; // Header line

    const int numEntries = 100000; // Number of entries to generate, can be adjust as per requrements

    for (int i = 0; i < numEntries; ++i) {
        // inputting integer value
        int value = 100+i; // can be assign as per choice
        outputFile << i << "," << value << "\n";
    }

    outputFile.close();
    std::cout << "Data generation complete. File: generated_data.csv" << std::endl;

    return 0;
}
