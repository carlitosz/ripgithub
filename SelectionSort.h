#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <iostream>
#include <string>
using namespace std;

// ============================================================================
// User defined classes.
// ============================================================================
#include "GenerateData.h"


// ============================================================================
// Executes selection sort.
// ============================================================================
class SelectionSort : public GenerateData {
    public:
        // ====================================================================
        // Beginning execution.
        // ====================================================================
        void execute(int topN) {
            cout << "Selecting top " << topN << " elements to sort." << endl;
            vector<short int> v(topN);

            cout << "Sorting..." << endl;
            for (int i = 0; i < topN; ++i) {
                v[i] = searchArray[i];
            }

            v = selectionSort(v, topN);

            cout << "Top " << topN << " elements have been sorted." << endl;
            cout << endl;
        }

        // ====================================================================
        // Executes the selection sort algorithm.
        // ====================================================================
        vector<short int> selectionSort(vector<short int> v, int n) {
            int i;
            int j;
            int mid;

            for (int i = 0; i < n - 1; ++i) {
                mid = i;
                for (int j = i + 1; j < n; ++j) {
                    if (v[j] < v[mid]) {
                        mid = j;
                    }
                }

                v = swap(v, mid, i);
            }

            return v;
        }

        // ====================================================================
        // Swaps two elements.
        // ====================================================================
        vector<short int> swap(vector<short int> v, short int m, short int i) {
            short int temp = v[m];
            v[m] = v[i];
            v[i] = temp;

            return v;
        }

        // ====================================================================
        // Constructs new objects of SelectionSort by populating them with
        // random strings.
        // ====================================================================
        SelectionSort(int arraySize) {
            size = arraySize;
            searchArray = generateShorts(arraySize);
            cout << endl;
            cout << "Created array of " << arraySize << " short ints." << endl;
        }

    private:
        int size;
        vector<short int> searchArray;
};

#endif /* SELECTION_SORT_H */