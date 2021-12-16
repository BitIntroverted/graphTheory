/*
 * 	Name: Lukas Friedrich
 * 	Graph Theory
 * 	Linked List class header
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "data.h"
#include <iostream>
using std::cout;
using std::endl;

class LinkedList {

public:

    LinkedList();
    ~LinkedList();

    bool addNode(int, int);
    bool deleteNode(int);
    bool getNode(int, Data*);
    void printList(bool = false);
    int getCount();
    bool clearList();
    bool exists(int);
    void printNodeCentricGraph();
    bool cleanList(int);
    Node* getlist();

private:

    Node* head;
    void addHead(Node*, Node*);
    void addTail(Node*, Node*);
    void addMiddle(Node*, Node*);

};

#endif /*LINKEDLIST_H*/
