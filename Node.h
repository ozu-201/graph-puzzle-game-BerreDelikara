//
// Created by Olcay Taner YILDIZ on 6.03.2023.
//

#ifndef DATASTRUCTURES_CPP_NODE_H
#define DATASTRUCTURES_CPP_NODE_H
#include <string>

using namespace  std;

class Node {
private:
    int data;
    Node* next;
    string data2;
public:
    explicit Node(int data);
    explicit Node(string data2);
    void setNext(Node* _next);
    Node* getNext();
    int getData();
    string to_string();
};


#endif //DATASTRUCTURES_CPP_NODE_H
