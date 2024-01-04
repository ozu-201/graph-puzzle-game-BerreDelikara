//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#ifndef DATASTRUCTURES_CPP_GRAPH_H
#define DATASTRUCTURES_CPP_GRAPH_H


#include <string>
#include <vector>
#include "EdgeList.h"
#include "../../General/AbstractGraph.h"

namespace list {

    class Graph : public AbstractGraph{
    private:
        EdgeList *edges;
    public:
        explicit Graph(int vertexCount);
        ~Graph();
        void addEdge(int from, int to);
        void addEdge(int from, int to, int weight);
        void connectedComponentsDisjointSet();
        Path* bellmanFord(int source);
        Path* dijkstra(int source);
        void prim();

        static std::vector<int> getSize(const std::string &filename1, const std::string &filename2);

        static void readData(const std::string &filename1, const std::string &filename2, Graph *graph3, Graph *graph4,
                      Graph *graph5);
        void breadthFirstSearchPath(const std::wstring &startWord, const std::wstring &endWord);

    protected:
        void depthFirstSearch(bool* visited, int fromNode) override;
        void breadthFirstSearch(bool* visited, int startNode) override;
        Edge* edgeList(int& edgeCount) override;

        static Graph *graph3;
        static Graph *graph4;
        static Graph *graph5;

        bool oneDifference(std::__cxx11::basic_string<wchar_t> word1, std::__cxx11::basic_string<wchar_t> word2);

        void addEdge();

        void printPath(int endNode, int *previous);

        int findNodeInGraph(std::wstring word, Graph *graph);


    };

}
#endif //DATASTRUCTURES_CPP_GRAPH_H
