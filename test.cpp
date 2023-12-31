#include <iostream>
#include <cassert>
#include "graph.h"

void printVector(vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

/**
 * This file tests the implementation of an undirected Graph data structure
 *
 */
int main2()
{
    cout << "Testing results:" << endl;
    //Testing adding edges
    Graph g(5);

    g.addUndirectedEdge(0, 1);
    g.addUndirectedEdge(0, 2);
    g.addUndirectedEdge(1, 2);
    g.addUndirectedEdge(1, 3);
    g.addUndirectedEdge(1, 4);
    g.addUndirectedEdge(2, 3);
    g.addUndirectedEdge(3, 4);

    //Displaying the vertices and connections
//    cout << "Print the graph using adjacency list" << endl;
//    g.printGraph();
//    for(int i = 0; i < g.getNumVerts(); i++) {
//        cout << "Vertex " << i << " has " << g.outDegree(i) << " outgoing edges" << endl;
//    }
//
//    // Adding a vertex
//    Vertex v1 = Vertex(5, "A");
//    g.addVertex(v1);
//    cout << "\nPrint the graph after adding a vertex" << endl;
//    g.printGraph();
//    assert(g.getNumVerts() == 6);
//
//    cout << "testing BFS from 3" << endl;
//    vector<int> list = g.BreadthFirstSearch(3);
//    printVector(list);
//    cout << endl;
//    cout << "testing DFS from 3" << endl;
//    list = g.DepthFirstSearch(3);
//    printVector(list);
//
//    cout << "testing BFS from 2" << endl;
//    list = g.BreadthFirstSearch(2);
//    printVector(list);
//    cout << endl;
//    cout << "testing DFS from 4" << endl;
//    list = g.DepthFirstSearch(4);
//    printVector(list);
//    cout << endl;
//
//    Graph g1(5);
//
//    g1.addUndirectedEdge(1, 0);
//    g1.addUndirectedEdge(0, 4);
//    g1.addUndirectedEdge(2, 1);
//    g1.addUndirectedEdge(0, 3);
//    g1.addUndirectedEdge(2, 4);
//
//    if (g1.checkCycle())
//        cout << "g1 contains a cycle" << endl;
//    else
//        cout << "g1 does not contain a cycle" << endl;
//
//    Graph g2(3);
//
//    g2.addUndirectedEdge(0, 1);
//    g2.addUndirectedEdge(1, 2);
//
//    if (g2.checkCycle())
//        cout << "g2 contains a cycle" << endl;
//    else
//        cout << "g2 does not contain a cycle" << endl;
//
    return 0;
}