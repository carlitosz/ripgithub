#include <iostream>
#include <chrono>
using namespace std;

// ============================================================================
// User defined classes.
// ============================================================================
#include "Hash.h"
#include "Queue.h"
#include "SelectionSort.h"
#include "MergeSort.h"

// ============================================================================
// Globals
// ============================================================================
// Change this var to sort different N (option 4)
const int TOP_N_TO_SORT = 200000;

// ============================================================================
// Function prototypes.
// ============================================================================
void printMenu();
void printResults(int);

// ============================================================================
// Main.
// ============================================================================
int main(void) {
    srand(static_cast<unsigned int>(time(0)));

    int input = -1;

    while (input != 0) {
        printMenu();
        cout << "Please choose from the menu: ";
        cin >> input;

        switch (input) {
            case 0:
                break;
            case 1: {
                Hash hashObj;
                hashObj.execute();
                hashObj.summary();
                break;
            }
            case 2: {
                cout << endl << "Nothing to execute... :(" << endl << endl;
                break;
            }
            case 3: {
                Queue queueObj;
                queueObj.execute();
                break;
            }
            case 4: {
                int userInput;

                cout << "Which algorithm would you like to run?" << endl;
                cout << "1) Selection sort" << endl;
                cout << "2) Merge sort" << endl;
                cin >> userInput;

                if (userInput == 1) {
                    SelectionSort s(100000);
                    auto started = std::chrono::high_resolution_clock::now();
                    s.execute(TOP_N_TO_SORT);
                    auto done = std::chrono::high_resolution_clock::now();
                    int milliseconds =
                        std::chrono::duration_cast<std::chrono::milliseconds>
                        (done - started).count();

                    printResults(milliseconds);
                } else {
                    MergeSort m(100000);
                    auto started = std::chrono::high_resolution_clock::now();
                    m.execute(TOP_N_TO_SORT);
                    auto done = std::chrono::high_resolution_clock::now();
                    int milliseconds =
                        std::chrono::duration_cast<std::chrono::milliseconds>
                        (done - started).count();

                    printResults(milliseconds);
                }
            }
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

// ============================================================================
// Prints the results to stdout.
// ============================================================================
void printResults(int milliseconds) {
    int seconds = (int) (milliseconds / 1000) % 60 ;
    int minutes = (int) ((milliseconds / (1000*60)) % 60);
    int hours   = (int) ((milliseconds / (1000*60*60)) % 24);

    cout << "Elapsed time: "
         << hours << " hour(s) "
         << minutes << " minute(s) "
         << seconds << " seconds "
         << milliseconds << " milliseconds."
         << endl;
}