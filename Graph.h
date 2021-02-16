#ifndef GRAPH_H
#include <iostream>
#include <list>
#include <deque>
#include <vector>

using namespace std;

class Graph {

private:

    int numberOfVertices; // No. of vertices
    vector<int> outDegrees; // Outdegree of a vertex
    vector<int> inDegrees; // Indegree of a vertex

    // Pointer to an array containing adjacency lists
    deque<int>* adjacencyDeque;

public:
    Graph(int numberOfVertices);

    ~Graph();

    void addEdge(int v, deque<int> w);
    bool isEuler();
    int graphSize();
    bool hasNonUsedEdge(int v);
    int getFirstNonUsedEdge(int v);
    void findFirstVertexInTheCircuitWithUnusedEdge(list<int> eulerianCircuit, int* firstNonVisited, int* firstNonVisitedIndex);
    list<int> hierHolzer(int s);
    void printEulerCircuit(list<int> eulerianCircuit);
};


#endif //GRAPH_H