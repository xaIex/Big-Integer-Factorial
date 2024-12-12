#include "BigInt.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    BigInt<int> largeInt;
    int input;
    ofstream outFile;
    outFile.open("output.txt");
    if (!outFile.is_open()) {
        cerr << "Error opening file";
        return -1;
    }

    while (true) {
        cout << "\nEnter number to calculate Factorial (1-500): ";
        cin >> input;
        if (cin.fail()) { // if user enters chararcter, prevents infinite loop and recovers
            cerr << "Invalid input. Please enter a valid integer.\n";
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            continue; // Go back to the start of the loop
        }
        if (input < 0 || input > 500) {
            cout << "Invalid input. Please enter valid input.\n";
            outFile << "Invalid input\n";
            continue;
        }

        largeInt.multiplyNode(input);
        cout << input << "! =  ";
        outFile << input << "! = ";
        largeInt.print(outFile);
        largeInt.~BigInt(); // clear list after calculation, otherwise inaccurate values

        cout << "\n\nCalculate Again?(Press any key to continue. Enter 'n' to quit): ";
        char choice;
        cin >> choice;
        if (choice == 'n') {
            cout << "Tasks Finsished!\n";
            outFile << "Tasks Finished!";
            break;
        }
        
    }
    outFile.close();
    return 0;
}