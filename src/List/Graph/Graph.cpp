//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#include <vector>
#include <iostream>
#include <fstream>
#include "Graph.h"
#include "../../Array/DisjointSet.h"
#include "../Queue.h"
#include "../../Array/Heap/MinHeap.h"

namespace list {
    Graph*Graph:: graph3=nullptr;
    Graph*Graph:: graph4=nullptr;
    Graph*Graph:: graph5=nullptr;

    Graph::Graph(int vertexCount) : AbstractGraph(vertexCount){
        edges = new EdgeList[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            edges[i] = EdgeList();
        }
    }

    Graph::~Graph() {
        delete[] edges;
    }

    void Graph::connectedComponentsDisjointSet() {
        Edge* edge;
        int toNode;
        DisjointSet sets = DisjointSet(vertexCount);
        for (int fromNode = 0; fromNode < vertexCount; fromNode++){
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                toNode = edge->getTo();
                if (sets.findSetRecursive(fromNode) != sets.findSetRecursive(toNode)){
                    sets.unionOfSets(fromNode, toNode);
                }
                edge = edge->getNext();
            }
        }
    }

    void Graph::depthFirstSearch(bool *visited, int fromNode) {
        Edge* edge;
        int toNode;
        edge = edges[fromNode].getHead();
        while (edge != nullptr){
            toNode = edge->getTo();
            if (!visited[toNode]){
                visited[toNode] = true;
                depthFirstSearch(visited, toNode);
            }
            edge = edge->getNext();
        }
    }

    void Graph::breadthFirstSearch(bool *visited, int startNode) {
        Edge* edge;
        int fromNode, toNode;
        Queue queue = Queue();
        queue.enqueue(new Node(startNode));
        while (!queue.isEmpty()){
            fromNode = queue.dequeue()->getData();
            edge = edges[fromNode].getHead();
            while (edge != nullptr) {
                toNode = edge->getTo();
                if (!visited[toNode]){
                    visited[toNode] = true;
                    queue.enqueue(new Node(toNode));
                }
                edge = edge->getNext();
            }
        }
    }

    Path *Graph::bellmanFord(int source) {
        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        for (int i = 0; i < vertexCount - 1; i++){
            for (int fromNode = 0; fromNode < vertexCount; fromNode++){
                edge = edges[fromNode].getHead();
                while (edge != nullptr){
                    int toNode = edge->getTo();
                    int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                    if (newDistance < shortestPaths[toNode].getDistance()){
                        shortestPaths[toNode].setDistance(newDistance);
                        shortestPaths[toNode].setPrevious(fromNode);
                    }
                    edge = edge->getNext();
                }
            }
        }
        return shortestPaths;
    }

    Path *Graph::dijkstra(int source) {
        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(shortestPaths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                if (newDistance < shortestPaths[toNode].getDistance()){
                    int position = heap.search(toNode);
                    heap.update(position, newDistance);
                    shortestPaths[toNode].setDistance(newDistance);
                    shortestPaths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }
        return shortestPaths;
    }

    Edge *Graph::edgeList(int& edgeCount) {
        Edge* list;
        edgeCount = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                edgeCount++;
                edge = edge->getNext();
            }
        }
        list = new Edge[edgeCount];
        int index = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                list[index] = Edge(edge->getFrom(), edge->getTo(), edge->getWeight());
                index++;
                edge = edge->getNext();
            }
        }
        return list;
    }

    void Graph::prim() {
        Path* paths = initializePaths(0);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(paths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            Edge* edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                if (paths[toNode].getDistance() > edge->getWeight()){
                    int position = heap.search(toNode);
                    heap.update(position, edge->getWeight());
                    paths[toNode].setDistance(edge->getWeight());
                    paths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }
    }
    void Graph:: addEdge(){
        for(int i=0;i<vertexCount;i++){
           wstring data1= edges[i].getHead()->getData();
            for(int j=0;j<vertexCount;j++){
                wstring data2= edges[j].getHead()->getData();
                if(oneDifference(data1,data2)){
                    edges[i].insert(new Edge(i,j,data2,1));
                }
            }

        }
    }
        bool Graph:: oneDifference(wstring word1,wstring word2){
            int count=0;
            for(int i=0;i<word1.length();i++){
                if(word1.at(i)==word2.at(i)){
                    count++;
                }
            }
            if(count==1){
                return true;
            }else{
                return false;
            }
        }

        void Graph::printPath(int endNode, int* previous){
        std::vector<int> path;

        int currentNode=endNode;
        while(currentNode!=-1){
            path.insert(path.begin(),currentNode);
            currentNode=previous[currentNode];

        }
        for(int node:path){
            Edge* edge=edges[node].getHead();
std::wcout<<edge->getData()<<L" ";
        }

    }
    void Graph::readData(const std:: string& filename1,const std:: string& filename2, Graph* graph3,Graph* graph4,Graph* graph5) {
        try {
            std::locale::global(std::locale("tr_TR.UTF-8"));

            std::wifstream filestream1(filename1);
            std::wifstream filestream2(filename2);
            if (!filestream1.is_open() || !filestream2.is_open()) {
                throw new std::runtime_error("Unable to open file");
            }
            int i = 0;
            int j = 0;
            int k = 0;

            std::wstring word;
            while (filestream1 >> word) {
                if (word.length() == 3) {
                    graph3->edges[i].insert(new Edge(i, i, word, 1));
                    i++;
                }
                if (word.length() == 4) {
                    graph3->edges[j].insert(new Edge(j, j, word, 1));
                    j++;
                }
                if (word.length() == 5) {
                    graph3->edges[k].insert(new Edge(k, k, word, 1));
                    k++;
                }

            }
            while (filestream2 >> word) {
                if (word.length() == 3) {
                    graph3->edges[i].insert(new Edge(i, i, word, 1));
                    i++;
                }
                if (word.length() == 4) {
                    graph3->edges[j].insert(new Edge(j, j, word, 1));
                    j++;
                }
                if (word.length() == 5) {
                    graph3->edges[k].insert(new Edge(k, k, word, 1));
                    k++;
                }

            }
            filestream1.close();
            filestream2.close();

            graph3->addEdge();
            graph4->addEdge();
            graph5->addEdge();

        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    std::vector<int> Graph::getSize(const std:: string& filename1,const std:: string& filename2){
try{
    std::locale::global(std::locale("tr_TR.UTF-8"));

    std::wifstream filestream1(filename1);
    std::wifstream filestream2(filename2);
    if(!filestream1.is_open()||!filestream2.is_open()){
        throw new std::runtime_error("Unable to open file");
    }
    int size3=0;
    int size4=0;
    int size5=0;

    std::wstring word;
    while(filestream1>>word) {
        if (word.length() == 3) {
            size3++;
        }
        if (word.length() == 4) {
            size4++;
        }
        if (word.length() == 5) {
            size5++;
        }
    }
        filestream1.close();
        while (filestream2 >> word) {
            if (word.length() == 3) {
                size3++;
            }
            if (word.length() == 4) {
                size4++;
            }
            if (word.length() == 5) {
                size5++;
            }
        }
        filestream2.close();
        std::vector<int> sizes = {size3, size4, size5};
        return sizes;
    }catch(const std::exception& e){
        std::cerr<<"Error: "<<e.what()<<std::endl;
    }
}

    void Graph::breadthFirstSearchPath(const std::wstring& startWord,const std:: wstring& endWord) {
        list::Graph* currentGraph;

        if(startWord.length()==3&& endWord.length()==3){
            currentGraph=graph3;
        }else if (startWord.length()==4&& endWord.length()==4){
                currentGraph=graph4;

            }else if (startWord.length()==5 && endWord.length()==5){
            currentGraph=graph5;

        }else{

            std::wcout<<"Wrong start or end length";
        }

int startNode=findNodeInGraph(startWord,currentGraph);
        int endNode=findNodeInGraph(startWord,currentGraph);

        bool* visited=new bool[currentGraph->vertexCount];
        int* previous =new int[currentGraph->vertexCount];

        for(int i=0;i<currentGraph->vertexCount;i++){
            visited[i]=false;
            previous[i]=-1;
        }
        Queue queue = Queue();
        queue.enqueue(new Node(startNode));
        while (!queue.isEmpty()){
            int neighbor = queue.dequeue()->getData();
           Edge* edge = edges[neighbor].getHead();

            while (edge != nullptr) {
              int  toNode = edge->getTo();
                if(!visited[toNode]){
                    visited[toNode]=true;
                    queue.enqueue(new Node(toNode));
                }
                if(neighbor==endNode){
                    printPath(endNode,previous);
                    return;
                }
                edge = edge->getNext();
            }
            }
    }
    int Graph:: findNodeInGraph(std::wstring word,Graph* graph){

        for(int i=0;i<graph->vertexCount;i++){
            if(edges[i].getHead()->getData()==word){
                return i;
            }
        }
        return -1;

    }
}