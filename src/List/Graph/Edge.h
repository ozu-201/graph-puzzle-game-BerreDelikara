//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#ifndef DATASTRUCTURES_CPP_EDGE_H
#define DATASTRUCTURES_CPP_EDGE_H



class Edge {
private:


    int from;
    int to;
    int weight;
    std::wstring data;
    Edge* next;
public:
    Edge();
    Edge(int from, int to, std::wstring data, int weight);
    void setNext(Edge* _next);
    Edge* getNext() const;
    int getFrom() const;
    int getTo() const;
    int getWeight() const;

    std::wstring getData() const;
};


#endif //DATASTRUCTURES_CPP_EDGE_H
