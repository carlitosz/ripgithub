#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <queue>
#include <string>
#include <unistd.h>
#include <time.h>
#include <cmath>
#include <chrono>
using namespace std;

// ============================================================================
// Global vars.
// ============================================================================
const int CUST_ARRIVAL = 240; // 4 mins

const float CLERK1 = 60; // 1/min
const float CLERK2 = 30; // .5/min
const float CLERK3 = 45; // .75/min

// Number of customers to put into the customer queue.
const int CUSTOMER_COUNT = 23;

// ============================================================================
// User defined classes.
// ============================================================================
#include "Clerk.h"
#include "Colors.h"
#include "Customer.h"
#include "BinarySearchTree.h"

// ==== Queue =================================================================
// The queue class creates a queue and measures the average wait time for
// customers in a line.
// ============================================================================
class Queue {
    public:
        Queue();
        void execute();

    private:
        queue<Customer> customerQueue;
        queue<Clerk> clerkQueue;
        queue<Clerk> reserveClerkQueue;
        queue<Clerk> inProcess;
        queue<Clerk> reserveInProcess;
        queue<float> waitTimeQueue;
        int customerCounter;
        time_t begTime;
        int maxCustomers;
        float avgWait;

        void printStats();
        void serviceNextCustomer();
        void addNewClerk(int customerCount);
        void elapsedTime();
        void checkCustomersDone();
        bool isDone();
        void checkNewArrival();
};

// ============================================================================
// Constructor.
// ============================================================================
Queue::Queue() {
    customerCounter = 1;
    maxCustomers = 0;
    avgWait = 0.00;

    Clerk c("Clerk1", CLERK1);
    Clerk c2("Clerk2", CLERK2);
    Clerk c3("Clerk3", CLERK3);

    clerkQueue.push(c);
    clerkQueue.push(c2);
    clerkQueue.push(c3);

    while (customerCounter <= CUSTOMER_COUNT) {
        string c = "customer " + to_string(customerCounter);
        Customer cust(c, 0);
        customerQueue.push(cust);
        customerCounter++;
    }

    cout << "***********************************************" << endl;
    cout << "There are " << clerkQueue.size() << " clerks available." << endl;
    cout << "The customer queue currently has "
         << customerQueue.size() << " customers." << endl;
    cout << "***********************************************" << endl;
}

// ============================================================================
// Executes the process.
// ============================================================================
void Queue::execute() {
    // Case 1: No customers left - Break
    // Case 2: Customers in line, clerks available – Service customer
    // Case 3: Customers in line, no clerks – Wait
    // Case 4: Every 5 customers in line, no clerks – Add new clerk
    begTime = time(0);
    elapsedTime();

    bool readyToStart = false;
    int clerkCounter = 1;
    while (1) {
        int extraClerksNeeded = floor(customerQueue.size() / 5);
        if (extraClerksNeeded == reserveClerkQueue.size()) break;
        addNewClerk(clerkCounter * 5);
    }

    do {
        if (customerQueue.size() == 0 && inProcess.size() == 0 && reserveInProcess.size() == 0) {
            break;
        }
        
        checkCustomersDone();

        int t = (int)difftime(time(0), begTime);
        if (t % CUST_ARRIVAL == 0 && t > 0) {
            cout << FRED_CYAN << "A new customer has arrived." << RST << endl;
            usleep(1000000); // Sleep 1 second.
            checkNewArrival();
        }

        if (customerQueue.size() > 0 && (clerkQueue.size() > 0 || reserveClerkQueue.size() > 0)) {
            serviceNextCustomer();
        }

        if (customerQueue.size() == 0) {
            cout << " There are no customers waiting." << endl;
            if (inProcess.size() || reserveInProcess.size()) {
                cout << FGREY_PURPLE << " Waiting on clerks to finish..."
                     << RST << endl;
                usleep(1000000); // Sleep 1 second.

                continue;
            }

            break;
        }

        if ((customerQueue.size() % 5) > 0) {
            elapsedTime();
            cout << FYELLOW_BLACK << " Waiting for next available clerk..."
                 << RST << endl;
            usleep(1000000); // Sleep 1 second.
            continue;
        }

        usleep(1000000);
        elapsedTime();
    } while (isDone());

    checkCustomersDone();
    printStats();
    return;
}

// ============================================================================
// Checks for arrival of a new customer.
// ============================================================================
void Queue::checkNewArrival() {
    string c = "customer " + to_string(customerCounter++);
    Customer cust(c, 0);
    customerQueue.push(cust);
}

// ============================================================================
// Checks if everything is done.
// ============================================================================
bool Queue::isDone() {
    if (customerQueue.size() == 0
        && inProcess.size() == 0
        && reserveInProcess.size() == 0) return false;

    return true;
}

// ============================================================================
// Checks if the customers are done being attended.
// ============================================================================
void Queue::checkCustomersDone() {
    if (inProcess.size() == 0 && reserveInProcess.size() == 0) {
        cout << FGREY_PURPLE << "All clerks are available." << RST << endl;
    }

    if (inProcess.size() > 0) {
        int i = 0;
        while (i < inProcess.size()) {
            Clerk c = inProcess.front();

            double soFar = difftime(time(0), c.getTimeStarted());
            if (soFar >= c.getTimeAllotted()) {
                cout << FBLACK_GREEN << "* * " << c.getName()
                     << " is now available * *" << RST << endl;
                inProcess.pop();
                clerkQueue.push(c);

                continue;
            }

            cout << c.getName() << " is busy." << endl;
            inProcess.pop();
            inProcess.push(c);
            i++;
        }
    }

    if (reserveInProcess.size() > 0) {
        int i = 0;
        while (i < reserveInProcess.size()) {
            Clerk c = reserveInProcess.front();

            double soFar = difftime(time(0), c.getTimeStarted());
            if (soFar >= c.getTimeAllotted()) {
                if (customerQueue.size() <= (c.getCustomerCount() - 5)) {
                    cout << FYELLOW_BLACK << c.getName()
                         << "'s shift has ended." << RST << endl;

                    reserveInProcess.pop();
                    continue;
                }

                cout << FBLACK_GREEN << "* * " << c.getName()
                     << " is now available * *" << RST << endl;
                reserveInProcess.pop();
                reserveClerkQueue.push(c);

                continue;
            }

            cout << c.getName() << " is busy." << endl;
            reserveInProcess.pop();
            reserveInProcess.push(c);
            i++;
        }
    }
}

// ============================================================================
// Service next customer.
// ============================================================================
void Queue::serviceNextCustomer() {
    if (clerkQueue.size() == 0 && reserveClerkQueue.size() == 0) {
        cout << "There are no clerks available." << endl;
    }

    Clerk c;
    if (clerkQueue.size() > 0) {
        c = clerkQueue.front();
        clerkQueue.pop();
        Customer cust = customerQueue.front();
        customerQueue.pop();

        c.setTimeStarted(time(0));
        cust.setTimeStarted(time(0));
        inProcess.push(c);
        cout << "– " << FBLACK_RED << c.getName()
             << " is now attending customer " << cust.getName() << RST << endl;

        return;
    }

    if (reserveClerkQueue.size() > 0) {
        c = reserveClerkQueue.front();
        reserveClerkQueue.pop();
        Customer cust = customerQueue.front();
        customerQueue.pop();

        c.setTimeStarted(time(0));
        cust.setTimeStarted(time(0));
        reserveInProcess.push(c);
        cout << "– " << FBLACK_RED << c.getName()
             << " is now attending customer " << cust.getName() << RST << endl;
    }
}

// ============================================================================
// Print stats.
// ============================================================================
void Queue::printStats() {
    cout << "Stats" << endl;
}

// ============================================================================
// Adds a new clerk to the reserve clerk queue.
// ============================================================================
void Queue::addNewClerk(int customerCount) {
    string c = "RESERVE CLERK " + to_string((clerkQueue.size() + 1) + reserveClerkQueue.size());
    Clerk clerk(c, CLERK1);
    clerk.setCustomerCount(customerCount);
    reserveClerkQueue.push(clerk);
    cout << clerk.getName() << " has been added to help with customers." << endl;
}

// ============================================================================
// Elapsed time.
// ============================================================================
void Queue::elapsedTime() {
    double elapsed = difftime(time(0), begTime);

    if ((int)elapsed % 1 == 0) printf("\n\nTime elapsed: %.0f seconds \n\n", elapsed);
}

#endif /* QUEUE_H */
