#include <iostream>
#include <fstream>  // For file handling
#include <cstdlib>  // For rand() function
#include <ctime>    // For seeding rand()

using namespace std;

int main() {
    // Seed the random number generator with the current time
    srand(time(0));

    // Create an ofstream object to write to the CSV file
    ofstream outfile("input1.csv");

    if (!outfile) {
        cerr << "Error creating file!" << endl;
        return 1;
    }

    // Define the number of random integers to generate (100000)
    int n = 100000;

    // Generate and write random integers to the CSV file
    for (int i = 0; i < n; ++i) {
        outfile << rand() % 100000;  // Random number between 0 and 99999

        // Add a comma after every number except the last one
        if (i != n - 1) {
            outfile << ",";
        }
    }

    // Close the file after writing
    outfile.close();
    cout << "CSV file created successfully with " << n << " random numbers." << endl;

    return 0;
}
