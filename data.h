#ifndef DATA_H
#define DATA_H

#include "string"
using std::string;

struct Data {
    int id;
    int weight;
};

struct Node {
    Data data;
    Node* next;
    Node* prev;
};

#endif /* DATA_H */