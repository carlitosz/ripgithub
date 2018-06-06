#ifndef NODE_H
#define NODE_H

struct Node {
    Node() : timesFound(0) { }

    string value;
    int timesFound;
    int height;
    Node *right;
    Node *left;
};

#endif /* NODE_H */
