#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
using namespace std;

class DoublyLinkedList {
    private:
        struct Link {
            Link() : index(0), timesFound(0) { }

            string data;
            int index;
            int timesFound;
            Link *next;     // Points to next link
            Link *prev;     // Points to previous link
        };

        Link *head;         // Points to first link
        int numElems;
    public:
        DoublyLinkedList() { head = NULL; numElems = 0; }
        ~DoublyLinkedList() {};
        void printList();
        void insert(string data);
        bool find(int index);
        int getNumElems() { return numElems; }
        void printSummary();
};

// ============================================================================
// Prints the summary of the data.
// ============================================================================
void DoublyLinkedList::printSummary() {
    Link *ptr = head;
    int counter = 0;
    cout << "Printing linked list [index] times found." << endl;
    while (ptr != NULL) {
        if (counter % 23 == 0) {
            cout << endl;
        }

        cout << "[" << ptr->index << "] " << ptr->timesFound << '\t';
        ptr = ptr->next;
        counter++;
    }

    cout << endl << endl;
}

// ============================================================================
// Finds the data in the linked list.
//
// Input -> the index to find at.
// Output -> true if found, else false. Also increments times found.
// ============================================================================
bool DoublyLinkedList::find(int index) {
    Link *ptr = head;
    while (ptr != NULL) {
        if (ptr->index == index) {
            ptr->timesFound++;
            return true;
        }

        ptr = ptr->next;
    }

    return false;
}
   
// ============================================================================
// printList.
//
// Input -> nothing.
// Output -> Prints the list.
// ============================================================================
void DoublyLinkedList::printList() {
    cout << "\n\nPrinting DoublyLinkedList.\n";
    cout << "NULL ";

    Link *ptr = head;
    while (ptr != NULL) {
        cout << " <- " << ptr->data << " -> ";
        ptr = ptr->next;
    }

    cout << "NULL" << endl;
}

// ============================================================================
// addList
//
// Input -> The value to add.
// Output -> nothing.
// ============================================================================
void DoublyLinkedList::insert(string data) {
    // Add to empty list
    if (head == NULL) {
        Link *temp = new Link;
        temp->prev = NULL;
        temp->next = NULL;
        temp->data = data;
        head = temp;
        numElems++;
        temp->index = numElems - 1;

        return;
    }

    // Append to end of list
    Link *ptr = head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }

    Link *temp = new Link;
    temp->prev = ptr;
    temp->next = NULL;
    temp->data = data;
    ptr->next = temp;
    numElems++;
    temp->index = numElems - 1;
}

#endif /* DOUBLY_LINKED_LIST_H */
