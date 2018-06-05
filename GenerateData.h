#ifndef GENERATE_DATA_H
#define GENERATE_DATA_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

// ============================================================================
// User defined constants.
// ============================================================================
const int STRING_SIZE = 3;
const string CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


// ==== Generate data =========================================================
// Generates data and test data for the linear, binary, and hash searches.
// ============================================================================
class GenerateData {
    public:
        // ====================================================================
        // Generates a single random string.
        // ====================================================================
        string generateString() {
            string randomStr = "";

            for(int i = 0; i < STRING_SIZE; i++) {
                randomStr += CHARS[rand() % CHARS.size()];
            }

            return randomStr;
        }
};

#endif /* GENERATE_DATA_H */
