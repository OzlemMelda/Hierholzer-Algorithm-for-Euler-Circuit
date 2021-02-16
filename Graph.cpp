#include "Graph.h"
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <deque>

using namespace std;

Graph::Graph(int numberOfVertices) {

    this->numberOfVertices = numberOfVertices;
    adjacencyDeque = new deque<int>[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
    {
        outDegrees.push_back(0);
        inDegrees.push_back(0);
    }
}

Graph::~Graph() {
    delete[] adjacencyDeque;
}

void Graph::addEdge(int v, deque<int> w) {
    adjacencyDeque[v].insert(adjacencyDeque[v].end(), w.begin(), w.end()); // Add w to v’s list.
}

bool Graph::isEuler() {

    bool isEuler = true;
    for (int i = 0; i < numberOfVertices; i++)
    {
        outDegrees[i] = adjacencyDeque[i].size();
        for (int j = 0; j < adjacencyDeque[i].size(); j++) {
            inDegrees[adjacencyDeque[i][j]]++;
        }
    }

    for (int i = 0; i < numberOfVertices; i++)
    {
        if (inDegrees[i] != outDegrees[i]){
            isEuler = false;
            break;
        }
    }
    return isEuler;
}

int Graph::graphSize() {

    // Get |E|
    int size = 0;
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < adjacencyDeque[i].size(); j++)
        {
            size++;
        }
    }
    return size;
}

bool Graph::hasNonUsedEdge(int v) {

    bool notVisited = false;

    if(outDegrees[v] > 0)
        notVisited = true;

    return notVisited;
}

int Graph::getFirstNonUsedEdge(int v) {

    int nonUsedEdgeVertex = -1;
    nonUsedEdgeVertex = adjacencyDeque[v].front();
    outDegrees[v]--;
    adjacencyDeque[v].pop_front();

    return nonUsedEdgeVertex;
}

void Graph::findFirstVertexInTheCircuitWithUnusedEdge(list<int> eulerianCircuit, int* firstNonVisited, int* firstNonVisitedIndex) {

    *firstNonVisited = -1;
    *firstNonVisitedIndex = -1;

    list<int>::iterator i;
    int index = 0;
    for (i = eulerianCircuit.begin(); i != eulerianCircuit.end(); ++i){
        if (outDegrees[*i] > 0) {
            *firstNonVisited = *i;
            *firstNonVisitedIndex = index;
            break;
        };
        if (*firstNonVisited != -1)
            break;
        index++;
    }
}

list<int> Graph::hierHolzer(int s) {

    // Create a list for eulerian
    list<int> eulerianCircuit;
    eulerianCircuit.push_back(s);
    int currentGraphSize = graphSize();

    int firstNonVisited = -1;
    int firstNonVisitedIndex = -1;
    list<int>::iterator it = eulerianCircuit.end();

    while (eulerianCircuit.size() < currentGraphSize) {

        vector<int> tour;

        while (hasNonUsedEdge(s)) {
            s = getFirstNonUsedEdge(s);
            tour.push_back(s);
        }

        eulerianCircuit.insert(it, tour.begin(), tour.end());

        findFirstVertexInTheCircuitWithUnusedEdge(eulerianCircuit, &firstNonVisited, &firstNonVisitedIndex);

        s = firstNonVisited;
        it = eulerianCircuit.begin();

        advance(it, firstNonVisitedIndex+1);  
    }

    return eulerianCircuit;
}

void Graph::printEulerCircuit(list<int> eulerianCircuit) {
    list<int>::iterator i;
    for (i = eulerianCircuit.begin(); i != eulerianCircuit.end(); ++i) {
        cout << *i << " ";
    }
}
