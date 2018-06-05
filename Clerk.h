#ifndef CLERK_H
#define CLERK_H

#include<string>
#include <time.h>

class Clerk {
    public:
        Clerk() { timeStarted = NULL; };
        Clerk(string n, float t) {
            name = n;
            time = t;
        }

        void setTimeStarted(time_t t) { timeStarted = t; }
        time_t getTimeStarted() { return timeStarted; }
        float getTimeAllotted() { return time; }
        string getName() { return name; }
        void setCustomerCount(int c) { customerCount = c; }
        int getCustomerCount() { return customerCount; }
    private:
        string name;
        time_t timeStarted;
        float time;
        int customerCount;
};

#endif /* CLERK_H */
