//
// Created by alvaro on 12/3/23.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "CityPathFinder.h"


/**
 * @brief Returns the data of the shortest poth between the origin point and all of the other nodes; there is a node which is connected to all the
 * other nodes
 * @param startVertex represent the id of the starting vertex
 * @param cities vector that contains vertexes of all the cities
 */
std::unordered_map<int, PathVertexInfo*> CityPathFinder::DijkstraShortestPath(int startVertex,
                                                      vector<Vertex> cities,
                                                      Graph graph) {

    std::unordered_map<int, PathVertexInfo*> info;

    vector<PathVertexInfo*> unvisited;


    for (Vertex vertex :cities) {


        PathVertexInfo* path_info = new PathVertexInfo(vertex.id);

        unvisited.push_back(path_info);

        info.insert({vertex.id,path_info});

    }


    info[startVertex]->distance = 0;


    while(unvisited.size()){

        PathVertexInfo* currentInfo = PathVertexInfo::RemoveMin(unvisited);


        for(Edge edge: graph.adjList[currentInfo->vertex_id]){
//            cout<<"from"<<edge.from_vertex<<":"<<edge.to_vertex<<endl;
            Vertex adjacentVertex = graph.vertices[edge.to_vertex];



//            cout<<"EDGE WEIGHT"<<edge.weight<<endl;

            int altDistance = currentInfo->distance + edge.weight;

            PathVertexInfo* adjInfo = info[adjacentVertex.id];


//            cout<<"Adj info id:"<<adjInfo->distance<<endl;
//            cout<<"Adj info di:"<<adjInfo->distance<<endl;


            if(altDistance < adjInfo->distance){
                info[adjacentVertex.id]->distance = altDistance;
                info[adjacentVertex.id]->predecessor = currentInfo->vertex_id;
            }


        }

    }


    return info;
}


std::string shortestPath( std::unordered_map<int, PathVertexInfo*> info,
                          const std::unordered_map<int, Vertex>& map,
                          int start,int end ){
    string path = "";
    int current = end;

    while(current != start){

        Vertex data = map.at(current);
        path = "-> " +std::to_string(current) + ":" + map.at(current).city_name + path;

        current = info[current]->predecessor;
    }
    path = map.at(current).city_name + path;

    return path;
}



int shortestPathDistance( std::unordered_map<int, PathVertexInfo*> info,
                          const std::unordered_map<int, Vertex>& map,
                          int start,int end ){
    string path = "";
    int current = end;
    int distance = 0;

    while(current != start){

        Vertex data = map.at(current);
        distance += info[current]->distance;
        current = info[current]->predecessor;

    }
    path = map.at(current).city_name + path;

//    return path;
    return  distance;
}




bool checkInput( std::unordered_map<string, Vertex> map ,
                  std::string nameId){

    if (auto search = map.find(nameId); search != map.end()){
        return true;
    }
    return false;

}





int main(int argc, char *argv[]){

    //lines 104 - 167  are all part of the set up of the project
    // this includes reading data from the txt files and
    // the creation of the Graph and Vertexes
    Graph roads(20);
    std::unordered_map<std::string, Vertex> nameIdMap;
    std::unordered_map<int, Vertex> idMap;
    vector<Vertex> cities;

    //adding edge data into the graph
    std::ifstream road_file("road.txt");
    if (!road_file.is_open()) {
        std::cerr << "Unable to open road_file" << std::endl;
    }

    std::string line;
    while (std::getline(road_file, line)) {

        std::istringstream iss(line);
        std::string from_city, to_city, distance;

        iss >> from_city >> to_city >> distance;

        int fc_val = std::stoi(from_city);
        int tc_val = std::stoi(to_city);
        float d_val = std::stof(distance);


        roads.addDirectedEdge(fc_val,tc_val,d_val);
    }

    road_file.close();

    //reading data from cty file

    std::ifstream city_file("city.txt");
    if (!city_file.is_open()) {
        std::cerr << "Unable to open city_file" << std::endl;
    }
    std::string line2;
    while (std::getline(city_file, line2)) {

        std::istringstream iss(line2);
        std::string id, s_id , city_name, population, elevation;

        iss >> id>> s_id >>city_name>>population >> elevation;

        int id_val = std::stoi(id);
        int pop_val = std::stoi(population);
        int elevation_val = std::stoi(elevation);

        Vertex city_data(id_val, s_id, city_name,pop_val,elevation_val);

        roads.addVertex(city_data);

        idMap[id_val] = city_data;
        nameIdMap[s_id] = city_data;

        cities.push_back(city_data);

    }

    city_file.close();


    std::unordered_map<int, PathVertexInfo*> info = CityPathFinder::DijkstraShortestPath(0,cities,roads);

    std::cout<<"Author: Bryce Walker and Alvaro Espinoza Merida"<<std::endl;
    std::cout<<"Date: xx/xx/20xx"<<std::endl;
    std::cout<<"Course: CS311 (Data structures and Algorithms)"<<std::endl;
    std::cout<<"Description : Program to find the shortest route between cities"<<std::endl;

    if (argc > 1) {

        if(!checkInput(nameIdMap, argv[1]) ){
            cout<<"Invalid city code:"<<argv[1]<<endl;
            return -1;
        }
        if(!checkInput(nameIdMap, argv[2])){
            cout<<"Invalid city code:"<<argv[2]<<endl;
            return -1;
        }
        cout <<"----------------------------------------------------------------"<<endl;
        cout<<"From "<<nameIdMap.find(argv[1])->second.toString()<<endl;
        cout<<"To "<<nameIdMap.find(argv[2])->second.toString()<<endl;

        int city1Id = nameIdMap.find(argv[1])->second.id;
        int city2Id = nameIdMap.find(argv[2])->second.id;

        cout<<"The shortest path from "<<nameIdMap.find(argv[1])->second.city_name<<" to "
        <<nameIdMap.find(argv[2])->second.city_name<<" is "<<
        to_string(shortestPathDistance(info,idMap,city1Id,city2Id))<<endl;
        cout<<"through the route: "<<shortestPath(info,idMap,city1Id,city2Id)<<endl;

    } else {
        std::cout << "ERROR : No arguments provided...." << std::endl;
    }

}


