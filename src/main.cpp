//
// Created by bd034030 on 1/4/2024.
//

#include "List/Graph/Graph.h"

int main(){
    const std::vector<int> &sizes = list::Graph::getSize("turkish-dictionary", "english-dictionary");

   list::Graph *graph3=new list::Graph(sizes[0]);
    list::Graph *graph4=new list::Graph(sizes[1]);

    list::Graph *graph5=new list::Graph(sizes[2]);

    list::Graph::readData("turkish-dictionary", "english-dictionary", graph3,graph4,graph5);

    list::Graph::breadthFirstSearchPath("ama","ada");

    return 0;
}