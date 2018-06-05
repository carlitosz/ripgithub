#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <iostream>
#include <string>
using namespace std;

// ============================================================================
// User defined classes.
// ============================================================================
#include "GenerateData.h"


// ============================================================================
// Executes MergeSort.
// ============================================================================
class MergeSort : public GenerateData {
    public:
        // ====================================================================
        // Beginning execution.
        // ====================================================================
        void execute(int topN) {
            cout << "Selecting top " << topN << " elements to sort." << endl;
            vector<short int> v(topN);

            for (int i = 0; i < topN; ++i) {
                v[i] = searchArray[i];
            }

            cout << "Sorting..." << endl;

            v = mergeSort(v, 0, topN);

            cout << "Top " << topN << " elements have been sorted." << endl;
            cout << endl;
        }

        // ====================================================================
        // Executes the MergeSort algorithm.
        // ====================================================================
        vector<short int> mergeSort(vector<short int> v, int l, int r) {
            if (l < r) {
                int m = l + (r - l)/2;

                mergeSort(v, l, m);
                mergeSort(v, m + 1, r);

                merge(v, l, m, r);
            }

            return v;
        }

        // ====================================================================
        // Merges two arrays.
        // ====================================================================
        vector<short int> merge(vector<short int> v, int l, int m, int r) {
            int i;
            int j;
            int k;
            int n1 = m - l + 1;
            int n2 = r - m;

            vector<short int> L(n1);
            vector<short int> R(n2);

            for (i = 0; i < n1; ++i)
                L[i] = v[l + i];
            for (j = 0; j < n2; ++j)
                R[j] = v[m + 1 + j];

            i = 0;
            j = 0;
            k = l;

            while (i < n1 && j < n2) {
                if (L[i] <= R[j]) {
                    v[k] = L[i];
                    i++;
                } else {
                    v[k] = R[j];
                    j++;
                }
                k++;
            }

            while (i < n1) {
                v[k] = L[i];
                i++;
                k++;
            }

            while (j < n2) {
                v[k] = R[j];
                j++;
                k++;
            }

            return v;
        }

        // ====================================================================
        // Constructs new objects of MergeSort by populating them with
        // random strings.
        // ====================================================================
        MergeSort(int arraySize) {
            size = arraySize;
            searchArray = generateShorts(arraySize);
            cout << endl;
            cout << "Created array of " << arraySize << " short ints." << endl;
        }

    private:
        int size;
        vector<short int> searchArray;
};

#endif /* MERGE_SORT_H */
