/*
 * 	Name: Lukas Friedrich
 * 	Graph Theory
 * 	Linked List class
 */

#include "linkedlist.h"

LinkedList::LinkedList() {
    head = NULL;
}

LinkedList::~LinkedList() {
    clearList();
    delete head;
}

bool LinkedList::addNode(int id, int weightInfo) {
    bool addedFlag = false;
    if (id > 0 && weightInfo > -1) {
        Node* current, * temp;
        current = head;
        while (current && id > current->data.id && current->next) {
            current = current->next;
        }
        if (!current || id != current->data.id) {
            temp = new Node;
            temp->data.id = id; temp->data.weight = weightInfo;
            addedFlag = true;
            if (!current || (current && id < head->data.id)) {
                addHead(current, temp);
            }
            else if (!current->next) {
                addTail(current, temp);
            }
            else { addMiddle(current, temp); }
        }
    }
    return addedFlag;
}

bool LinkedList::deleteNode(int id) {
    bool isDeleted = false;
    if (id > 0) {
        Node* current = head;
        while (current && current->next && id != current->data.id) {
            current = current->next;
        }
        if (current && id == current->data.id) {
            if (!current->prev && current->next) { //replace head
                current->next->prev = NULL;
                head = current->next;
            }
            else if (!current->next && current->prev) { //replace tail
                current->prev->next = NULL;
            }
            else if (current->next && current->prev) { //replace middle
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            else if (!current->prev && !current->next) { //solo node case
                head = current->next;
            }
            delete current;
            isDeleted = true;
        }
    }
    return isDeleted;
}
bool LinkedList::getNode(int id, Data* tempData) {
    bool exists = false;
    if (id > 0) {
        Node* current = head;
        while (current && current->data.id != id)
        {
            current = current->next;
        }
        if (current && current->data.id == id) {
            tempData->id = current->data.id;
            tempData->weight = current->data.weight;
            exists = true;
        }
    }
    return exists;
}
void LinkedList::printList(bool backward) {
    Node* current = head;
    if (backward == false) {
        while (current) {
            std::cout << "-->" << current->data.id;
            current = current->next;
        }
    }
    else {
        while (current && current->next) {
            current = current->next;
        }
        while (current) {
            std::cout << "-->" << current->data.id;
            current = current->prev;
        }
    }
    if (current == head) {
        std::cout << "Empty";
    }
}

int LinkedList::getCount() {
    Node* current = head;
    int counter = 0;
    if (current) { counter = 1; }
    while (current && current->next) {
        counter++;
        current = current->next;
    }
    return counter;
}

bool LinkedList::clearList() {
    Node* temp;
    Node* current = head;
    bool cleared = false;
    while (current)
    {
        temp = current->next;
        delete current;
        current = temp;
    }
    head = NULL; cleared = true;
    return cleared;
}

bool LinkedList::exists(int id) {
    bool exists = false;
    Node* current = head;
    while (current && current->data.id != id)
    {
        current = current->next;
    }
    if (current && current->data.id == id) {
        exists = true;
    }
    return exists;
}

void LinkedList::printNodeCentricGraph()
{
    Node* current = head;
        while (current) {
            if(current->data.weight != -1){ //-1 indicates vertex
                std::cout << "--> ID: " << current->data.id << "|" << current->data.weight << " ";
            }
            current = current->next;
        }

}

//removes edge nodes from deleted vertex
bool LinkedList::cleanList(int id)
{
    Node* current = head;
    bool removed = false;
    while (current) {
        if (current->data.id = id) { //deleted vertex ID matches node ID
            deleteNode(id);
            removed = true;
            break;
        }
        current = current->next;
    }
    return removed;
}

Node* LinkedList::getlist()
{
    Node* current = head;
    return current;
}

void LinkedList::addHead(Node* current, Node* temp)
{
    if (current) {
        head->prev = temp;
    }
    temp->next = head;
    temp->prev = NULL;
    head = temp;
}
void LinkedList::addTail(Node* current, Node* temp)
{
    temp->next = NULL;
    temp->prev = current;
    current->next = temp;
}
void LinkedList::addMiddle(Node* current, Node* temp)
{
    temp->next = current;
    temp->prev = current->prev;
    current->prev->next = temp;
    current->prev = temp;
}