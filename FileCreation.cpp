#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::string fileName;
    int numEntries;

    // Get the file name and number of entries from the user
    std::cout << "Enter the name of the file: ";
    std::cin >> fileName;

    std::cout << "Enter the number of entries to generate: ";
    std::cin >> numEntries;

    // Open the file
    std::ofstream outputFile(fileName);
    
    // Check if the file opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file!" << std::endl;
        return 1;
    }

    outputFile << "index,value\n"; // Header line

    // Write the data to the file
    for (int i = 0; i < numEntries; ++i) {
        int value = 100 + i; // Value generation logic, can be adjusted as required
        outputFile << i << "," << value << "\n";
    }

    outputFile.close(); // Close the file

    // Output the details to the user
    std::cout << "Data generation complete." << std::endl;
    std::cout << "File: " << fileName << std::endl;
    std::cout << "Number of entries: " << numEntries << std::endl;

    return 0;
}
