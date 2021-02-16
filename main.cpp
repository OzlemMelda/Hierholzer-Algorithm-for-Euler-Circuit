#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <deque>
#include <algorithm>
#include <time.h>
#include "Graph.h"

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(cont));
}

int main(int argc, char const* argv[]) {

    //cout << time(0) << endl;

    string inputFile = argv[1];
    string outputFile = argv[2];

    ifstream infile(inputFile);

    // Create a graph
    string line;
    getline(infile, line);
    int numberOfVertices = stoi(line);

    Graph g(numberOfVertices);
    
    for (int i = 0; i < numberOfVertices; i++)
    {
        getline(infile, line);
        deque<string> edgesString;
        split1(line, edgesString);
        deque<int> edgesInt;

        std::transform(edgesString.begin(), edgesString.end(), std::back_inserter(edgesInt),
            [](const std::string& str) { return std::stoi(str); });

        edgesInt.pop_front();
        edgesInt.pop_front();
        g.addEdge(i, edgesInt);

    }

    getline(infile, line);
    int firstVertice = stoi(line);

    ofstream myfile(outputFile);
    myfile << std::fixed;

    // Find euler
    if (g.isEuler()) {
        list<int> euler;
        euler = g.hierHolzer(firstVertice);

        list<int>::iterator i;
        for (i = euler.begin(); i != euler.end(); ++i) {
            myfile << *i << " ";
        }
    }
    else {
        myfile << "no path";
    }

    //cout << time(0) << endl;

    return 0;
}