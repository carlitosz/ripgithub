#ifndef HASH_H
#define HASH_H

#include <iostream>
using namespace std;

// ============================================================================
// User defined classes.
// ============================================================================
#include "DoublyLinkedList.h"
#include "GenerateData.h"

// ============================================================================
// Global constants.
// ============================================================================
const int HASH_SIZE = 512;


// ==== Hash ==================================================================
// Hash class to test the distribution of hashes across a 512 linked list.
// ============================================================================
class Hash : public GenerateData {
    public:
        Hash();
        void execute();
        void summary();
        int generateHash(string str);
    private:
        DoublyLinkedList list;
};


// ============================================================================
// Constructor.
// ============================================================================
Hash::Hash() {
    cout << endl
         << "Generating " << HASH_SIZE
         << " strings for linked list." << endl;

    for (int i = 0; i < HASH_SIZE; ++i) {
        list.insert(generateString());
    }

    cout << "Finished generating strings." << endl;
}

// ============================================================================
// Executes the process.
//
// Input -> nothing.
// Output -> nothing.
// ============================================================================
void Hash::execute() {
    cout << "Beginning execution..." << endl;

    for (int i = 0; i < HASH_SIZE; ++i) {
        int hash = generateHash(generateString());
        list.find(hash);
    }

    cout << "Finished execution." << endl << endl;;
    return;
}

// ============================================================================
// Prints the summary of found matches.
//
// Input -> nothing.
// Output -> nothing.
// ============================================================================
void Hash::summary() {
    list.printSummary();
}

// ============================================================================
// Generates the hash.
//
// Input -> the string to hash.
// Output -> an integer hash.
// ============================================================================
int Hash::generateHash(string str) {
    unsigned int hash = 521;

    for (size_t i = 0; i < str.size(); ++i) {
        hash = 33 * hash + (unsigned char)str[i];
    }
    
    return hash % HASH_SIZE;
}

#endif /* HASH_H */
