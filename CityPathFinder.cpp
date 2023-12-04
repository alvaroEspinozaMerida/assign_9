//
// Created by alvaro on 12/3/23.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "CityPathFinder.h"



std::unordered_map<int, PathVertexInfo*> CityPathFinder::DijkstraShortestPath(int start_vertex,
                                                      vector<Vertex> cities,
                                                      Graph graph) {

    std::unordered_map<int, PathVertexInfo*> info;

    vector<PathVertexInfo*> unvisited;


    for (Vertex vertex :cities) {


        PathVertexInfo* path_info = new PathVertexInfo(vertex.id);

        unvisited.push_back(path_info);

        info.insert({vertex.id,path_info});

    }


    info[start_vertex]->distance = 0;


    while(unvisited.size()){

        PathVertexInfo* currentInfo = PathVertexInfo::RemoveMin(unvisited);


        for(Edge edge: graph.adjList[currentInfo->vertex_id]){
//            cout<<"from"<<edge.from_vertex<<":"<<edge.to_vertex<<endl;
            Vertex adjacentVertex = graph.vertices[edge.to_vertex];

//            cout<<"EDGE WEIGHT"<<edge.weight<<endl;

            int altDistance = currentInfo->distance + edge.weight;

            PathVertexInfo* adjInfo = info[adjacentVertex.id];

//            cout<<"Adj info:"<<adjInfo->distance<<endl;


            if(altDistance < adjInfo->distance){
                info[adjacentVertex.id]->distance = altDistance;
                info[adjacentVertex.id]->predecessor = currentInfo->vertex_id;
            }


        }

    }


    return info;
}



int main(){

    Graph roads(20);
    std::unordered_map<std::string, Vertex> map;

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

        cout<<line2<<endl;

        iss >> id>> s_id >>city_name>>population >> elevation;

        int id_val = std::stoi(id);
        int pop_val = std::stoi(population);
        int elevation_val = std::stoi(elevation);

        Vertex city_data(id_val, s_id, city_name,pop_val,elevation_val);

//        map[s_id] = city_data;
        cities.push_back(city_data);

    }

    city_file.close();


//    roads.printGraph();

    std::cout<<"Author: Bryce Walker and Alvaro Espinoza Merida"<<std::endl;
    std::cout<<"Date: xx/xx/20xx"<<std::endl;
    std::cout<<"Course: CS311 (Data structures and Algorithms)"<<std::endl;
    std::cout<<"----------------------------------------------------------------"<<std::endl;
    std::cout<<"Author: Bryce Walker and Alvaro Espinoza Merida"<<std::endl;



    std::unordered_map<int, PathVertexInfo*> info = CityPathFinder::DijkstraShortestPath(0,cities,roads);

    PathVertexInfo::print_path_vertex_info(info);






}


