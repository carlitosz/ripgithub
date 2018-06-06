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
#include "Graph.h"

// ============================================================================
// Globals
// ============================================================================
// Change this var to sort different N (option 4)
const int TOP_N_TO_SORT = 1000;
const int RANDOM_STRINGS = 512;

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

                break;
            }
            case 5: {
                BinarySearchTree *tree = new BinarySearchTree();
                cout << endl << "Filling binary tree with " << RANDOM_STRINGS
                     << " random strings." << endl;
                for (int i = 0; tree->getSize() < RANDOM_STRINGS; ++i) {
                    tree->insert();
                }

                cout << "There are now " << tree->getSize() << " strings "
                     << "in the tree." << endl << endl;

                cout << "Searching..." << endl << endl;
                for (int i = 0; i < RANDOM_STRINGS; ++i) {
                    tree->search();
                }

                break;
            }
            case 6: {
                int n = 7; // Number of cities
                Graph g(n);
                // SFO 0, DFW 1, LAX 2, ORD 3, JFK 4, MIA 5, BOS 6
                g.addEdge(0, 2, 338);
                g.addEdge(0, 6, 2703);
                g.addEdge(0, 1, 1463);
                g.addEdge(0, 3, 1847);
                g.addEdge(1, 3, 801);
                g.addEdge(1, 5, 1122);
                g.addEdge(2, 1, 1234);
                g.addEdge(2, 5, 2341);
                g.addEdge(3, 4, 741);
                g.addEdge(4, 6, 188);
                g.addEdge(5, 4, 1081);
                g.addEdge(5, 6, 1257);
            }
        }
    }

    return 0;
}

// ============================================================================
// Adds edge in a directed graph.
// ============================================================================
void addEdge(vector<int> adj[], int u, int v) {
    adj[u].push_back(v);
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