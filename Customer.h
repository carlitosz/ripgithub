#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

class Customer {
    public:
        Customer() { timeStarted = 0; }
        Customer(string n, int t) { name = n; timeStarted = t; }
        void setName(string n) { name = n; }
        string getName() { return name; }
        void setTimeStarted(int t) { timeStarted = t; }
        int getTimeStarted() { return timeStarted; }
    private:
        string name;
        int timeStarted;
};

#endif /* CUSTOMER_H */
