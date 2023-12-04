//
// Created by alvaro on 12/3/23.
//

#ifndef ASSIGN_9_CITYPATHFINDER_H
#define ASSIGN_9_CITYPATHFINDER_H
#include <vector>
#include "graph.h"

#include <unordered_map>

class CityPathFinder {

    public:

    static std::unordered_map<int, PathVertexInfo*>  DijkstraShortestPath(int start_vertex, vector<Vertex> cities, Graph graph);






};


#endif //ASSIGN_9_CITYPATHFINDER_H
