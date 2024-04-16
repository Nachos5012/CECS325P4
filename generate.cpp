//Krisha Hemani
// Class (CECS 325)
// Project Name (Prog 4 -contest uinsg pThreads)
// Due Date (03/28/2024)
//
// I certify that this program is my own original work. I did not copy any part of this program// from any other source. I further certify that I typed each and every line of code in this 
// program
//generate.cpp
#include <iostream>
#include <fstream>
#include <cstdlib> // For atoi()
#include <ctime>   // For time()

using namespace std;

void generate(int count, int min, int max) {
    // Open the output file
    if (count <= 0) {
        cerr << "Error: COUNT must be a positive integer." << endl;
        exit(1);
        }
    ofstream outputFile("numbers.dat");
    if (!outputFile) {
        cerr << "Error: Unable to create file 'numbers.dat'." << endl;
        exit(1);
    }

    // Seed the random number generator
    srand(time(nullptr));

    // Generate 'count' random numbers between 'min' and 'max' and write to file
    for (int i = 0; i < count; ++i) {
        int randomNumber = rand() % (max - min + 1) + min;
        outputFile << randomNumber << endl;
    }

    // Close the output file
    outputFile.close();

    cout << "Generated " << count << " random numbers between " << min << " and " << max << " in numbers.dat" << endl;
}

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " COUNT MIN MAX" << endl;
        return 1;
    }

    // Parse command line arguments
    int count = atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    // Generate random numbers and write to file
    generate(count, min, max);

    return 0;
}


