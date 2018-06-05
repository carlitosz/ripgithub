#include <iostream>
using namespace std;

// ============================================================================
// User defined classes.
// ============================================================================
#include "Hash.h"

// ============================================================================
// Function prototypes.
// ============================================================================
void printMenu();


// ============================================================================
// Main.
// ============================================================================
int main(void) {
    int input = -1;

    while (input != 0) {
        printMenu();
        cout << "Please choose from the menu: ";
        cin >> input;

        switch (input) {
            case 0:
                break;
            case 1:
                Hash hashObj;
                hashObj.execute();
                hashObj.summary();
                break;
        }
    }

    return 0;
}

// ============================================================================
// Prints the menu to stdout.
//
// Input -> nothing.
// Output -> the menu.
// ============================================================================
void printMenu() {
    cout << "1) Hashing" << endl;
    cout << "2) Stacks" << endl;
    cout << "3) Queues" << endl;
    cout << "4) Sorting" << endl;
    cout << "5) Binary Trees" << endl;
    cout << "6) Weighted Graph" << endl;
    cout << "0) Quit" << endl;
}
