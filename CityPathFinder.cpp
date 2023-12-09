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

/**
 * @brief Returns a string representing the shortest path between a start point and end point
 * @param info data representing the shortest path data between the start point and all other points
 * @param map data representing the map of the vertex based on the string key
 * @param start starting index vertex
 * @param end ending index vertex
 */
std::string shortestPath( std::unordered_map<int, PathVertexInfo*> info,
                          const std::unordered_map<int, Vertex>& map,
                          int start,int end ){
    string path = "";
    int current = end;

    while(current != start){

        path = "-> " + map.at(current).city_name + path;

        current = info[current]->predecessor;
    }
    path = map.at(current).city_name + path;

    return path;
}


/**
 * @brief Returns a string representing the shortest path between a start point and end point
 * @param roads data that represents the paths betweent the two vertices
 * @param end ending index vertex
 * @param start starting index vertex
 */
int distanceFromEdge(Graph roads , int end, int start){

    vector<Edge> adjList = roads.adjList[start];
    for (Edge e : adjList){

        if(e.to_vertex == end){
            return e.weight;
        }

    }
    return 0;
}


/**
 * @brief returns int representing the distance between start and end index
 * @param info data that represents the shortest distance between start and end point
 * @param roads data strucure repesents paths between vertices
 * @param start start point vertex
 * @param end end point vertex
 */
int shortestPathDistance( std::unordered_map<int, PathVertexInfo*> info,
                          Graph roads,
                          int start,int end ){
    int current = end;
    int distance = 0;

    while(current != start){


        distance += distanceFromEdge(roads,current,info[current]->predecessor);
        current = info[current]->predecessor;

    }

    return  distance;
}






/**
 * @brief checks the input given on CL
 * @param map  data representing the map of the vertex based on the string key
 * @param nameId id currently being verified to exist
 */
bool checkInput( std::unordered_map<string, Vertex> map ,
                  std::string nameId){

    if (auto search = map.find(nameId); search != map.end()){
        return true;
    }
    return false;

}

/**
 * @brief checks if a valid path exist betweent the points
 * @param info data that represents the shortest distance between start and end point
 *
 */
bool checkValidPathData(std::unordered_map<int, PathVertexInfo*> info){
    for (auto it = info.begin(); it != info.end(); ++it) {

        if(it->second->distance < 0){
            return false;
        }
    }
    return true;
}
/**
 * @brief loads the data into the data structures needed for the program to run
 * @param nameIdMap
 * @param idMap
 * @param cities
 *
 */

void loadData(Graph& roads,std::unordered_map<std::string, Vertex>& nameIdMap,
              std::unordered_map<int, Vertex>& idMap ,vector<Vertex>& cities){


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


}




int main(int argc, char *argv[]){
    //Creation of data structures that store important data about
    // the vertex and edges of the cities and roads
    Graph roads(20);
    std::unordered_map<std::string, Vertex> nameIdMap;
    std::unordered_map<int, Vertex> idMap;
    vector<Vertex> cities;

    //loading of the data into the apportipate data strucutres;method reads data from txt files
    //adds the right data into the files
    loadData(roads,nameIdMap,idMap,cities);


    std::cout<<"Author: Bryce Walker and Alvaro Espinoza Merida"<<std::endl;
    std::cout<<"Date: xx/xx/20xx"<<std::endl;
    std::cout<<"Course: CS311 (Data structures and Algorithms)"<<std::endl;
    std::cout<<"Description : Program to find the shortest route between cities"<<std::endl;

    //checks if the appropiate number of cities have been passed as arguments in CL
    if (argc > 1) {

        //verifies that the user has passed in valid cities that exist within the datastrucutres
        if(!checkInput(nameIdMap, argv[1]) ){
            cout<<"Invalid city code:"<<argv[1]<<endl;
            return -1;
        }
        if(!checkInput(nameIdMap, argv[2])){
            cout<<"Invalid city code:"<<argv[2]<<endl;
            return -1;
        }
        //display the cities data using a toString
        cout <<"----------------------------------------------------------------"<<endl;
        cout<<"From "<<nameIdMap.find(argv[1])->second.toString()<<endl;
        cout<<"To "<<nameIdMap.find(argv[2])->second.toString()<<endl;

        //city ids extracted in order to be used in finding the shortest path alg
        int city1Id = nameIdMap.find(argv[1])->second.id;
        int city2Id = nameIdMap.find(argv[2])->second.id;


        std::unordered_map<int, PathVertexInfo*> info = CityPathFinder::DijkstraShortestPath(city1Id,cities,roads);

        //final if statement that checks that a valid path between city1 and city2 exist
        if(checkValidPathData(info)){
            cout<<"The shortest path from "<<nameIdMap.find(argv[1])->second.city_name<<" to "
                <<nameIdMap.find(argv[2])->second.city_name<<" is "<<
                to_string(shortestPathDistance(info,roads,city1Id,city2Id))<<endl;
            cout<<"through the route: "<<shortestPath(info,idMap,city1Id,city2Id)<<endl;
        }
        //program exits if no route is found
        else{
            cout<<"No route from "<<nameIdMap.find(argv[1])->second.city_name<<" to "
                <<nameIdMap.find(argv[2])->second.city_name<<endl;
        }

    }
    //exits if no arguments found
    else {
        std::cout << "ERROR : No arguments provided...." << std::endl;
    }
    return  0 ;
}


