#include "graph.h"

// @brief Construct a Graph with the given number of vertices.
// @param nV The number of vertices in the graph.
Graph::Graph(int nV)
{
    numVerts = nV;

    for(int i = 0; i < nV ; i++){
        vector<Edge> newE;
        adjList.push_back(newE);
    }

}

// @brief destructor
Graph::~Graph()
{
}

// @brief add a vertex to the graph
void Graph::addVertex(Vertex v)
{
    //verticies get added into the verticies list
//    numVerts += 1;
    vertices.push_back(v);
    //new edge list gets added to adj list to represent new list of
    //adjacent verticies to this vertex
//    vector<Edge> newE;
//    adjList.push_back(newE);


}

// @brief add a directed edge v1->v2 to the graph
void Graph::addDirectedEdge(int v1, int v2, float weight)
{
    //directed edge gets added so we must create two edges that go to and from one edge to the other
    Edge newE(v1,v2,weight);
    adjList[v1].push_back(newE);
}

// @brief add an undirected edge to the graph
void Graph::addUndirectedEdge(int v1, int v2, float weight)
{

    //undirected edge gets added in so we must create two edges that go to and from and vise versa and place in each
    //respective vertex

    Edge newE1(v1,v2,weight);
    Edge newE2(v2,v1,weight);

    adjList[v1].push_back(newE1);
    adjList[v2].push_back(newE2);


}

// @brief the number of outgoing edges from a vertex
int Graph::outDegree(int v)
{
    return adjList[v].size();
}

bool contains(const std::vector<int>& vec, int value) {
    for (int elem : vec) {
        if (elem == value) {
            return true;
        }
    }
    return false;
}

// @brief depth first search from vertex v
vector<int> Graph::DepthFirstSearch(int v)
{
    //two vectors that keep track of the visted and a set
    //NOTE: vector is treated like  a stack using the back and pop_back functions to
    //equilenet of pop and front
    vector<int> vertexStack;
    vector<int> visitedSet;

    //add starting vertex to stack
    vertexStack.push_back(v);
    //while the stack is not empty we loop meaning we still have vertexs to check
    while(vertexStack.size() > 0 ){
        //current vertex is grabbed from the front of the stack ie back of vector
        int current = vertexStack.back();
//        cout<<"Vertex Back(top):"<<current<<endl;
        //front value on stack popped
        vertexStack.pop_back();
        //if the visted doesnt cotain current that means we should place it in the visited vector
        //and also add its adjacent values on to the stack so we can visit those next
        //stack is eventually emptied because all the values in the stack are already visited
        if(!contains(visitedSet,current)){
            visitedSet.push_back(current);

            for(int j = adjList[current].size()-1 ; j >= 0;j--){
                //gets the adj vertex
                int adj =  adjList[current][j].to_vertex;
                vertexStack.push_back(adj);
            }
        }

    }
    return visitedSet;

}


// @brief breadth first search from a vertex
vector<int> Graph::BreadthFirstSearch(int v)
{
    //three list represent visited vertex, frontier of values to vist, and discovered values
    vector<int> visited;
    queue<int> frontier;
    vector<int> discovered;
    //froniter has the starting vertex added in
    //discovered has starting vertex added in
    frontier.push(v);
    discovered.push_back(v);
    //current is set to vertex
    int current = v;
    //while the frontier is full we keep looping
    while (frontier.size() > 0 ){
        //current is set to front of frontier
        current = frontier.front();
        //frontier has value popped off
        frontier.pop();
        //visiited has value added to it
        visited.push_back(current);
        //loop through adjacent values of current vertex and add values not
        // in discovered into the frontier and discovered vector
        for(int j = 0 ; j < adjList[current].size();j++){
            //gets the adj vertex
            int adj =  adjList[current][j].to_vertex;


            if(!contains(discovered,adj)){
                frontier.push(adj);
                discovered.push_back(adj);
            }

        }

    }
    return visited;
}

/**
 * @brief Check if the graph has cycles
 * @return true if the graph has cycles
 */
 //function uses same exact algoritham as DFS however we added an extra if that
 //checks if the vertex stack already contain a value of an adj vertex then it indicates we
 //have a cycle because there should be only unique values for their not to be a cycle
bool Graph::checkCycle()
{
    bool cycle = false;
    vector<int> vertexStack;
    vector<int> visitedSet;

    vertexStack.push_back(0);

    while(vertexStack.size() > 0 ){

        int current = vertexStack.back();

//        cout<<"Vertex Back(top):"<<current<<endl;

        vertexStack.pop_back();

        if(!contains(visitedSet,current)){
            visitedSet.push_back(current);

            for(int j = adjList[current].size()-1 ; j >= 0;j--){
                //gets the adj vertex
                int adj =  adjList[current][j].to_vertex;
                if(contains(vertexStack,adj)){
                    cycle = true;
                    break;
                }
                vertexStack.push_back(adj);


            }

        }

    }
    return cycle;
}

// @brief print the graph
void Graph::printGraph()
{
    cout << "Graph:" << endl;
    for (int i = 0; i < numVerts; i++)
    {
        cout << i << ": ";
        for(auto j = adjList[i].begin(); j != adjList[i].end(); ++j)
        {
            cout << (*j).to_vertex << " " ;
        }
        cout << endl;
    }
    cout << endl;
}
