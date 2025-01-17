#include <map>
#include <iostream>
#include "vertex.h"
using namespace std;

/*
Method Name: Constructor
Method Description: Initalize a vertex in the graph
*/
Graph::Graph(string name, int connections, int cost){
    vertex_collection[name] = new vertex;
    vertex_collection[name]->cost = cost;
    vertex_collection[name]->name = name;
    vertex_collection[name]->connections_count = connections;
    vertex_collection[name]->connections = new vertex*[connections];
}

/*
Method Name: Destructor
Method Description: Deletes the graph from the heap
*/
Graph::~Graph(){
    for (auto it = vertex_collection.begin(); it != vertex_collection.end(); it++)
    {
        delete vertex_collection[it->first];
        delete [] it->second->connections;
    }
}

/*
Method Name: Add_Vertex
Method Description: Adds a vertex to the graph
*/
void Graph::Add_Vertex(string from, string name, int connections, bool bidirectional, int cost){
    //check if from exists
    if (!(vertex_collection[from])){
        vertex_collection.erase(from);
        cout << "Error, could not find " << from << "\n";
        return;
    }

    //check if from is full
    if (vertex_collection[from]->connections_used == vertex_collection[from]->connections_count){
        cout << "Error, max connections reached on " << from << "\n";
        return;
    }

    //add the vertex
    vertex_collection[name] = new vertex;
    vertex_collection[name]->cost = cost;
    vertex_collection[name]->name = name;
    vertex_collection[name]->connections_count = connections;
    vertex_collection[name]->connections = new vertex*[connections];
    vertex_collection[from]->connections[vertex_collection[from]->connections_used] = vertex_collection[name];
    vertex_collection[from]->connections_used++;

    //if the connection is bidirectional, add another edge
    if (bidirectional){
        vertex_collection[name]->connections[vertex_collection[name]->connections_used] = vertex_collection[from];
        vertex_collection[name]->connections_used++;
    }
}

/*
Method Name: connect_existing
Method Description: Connects two nodes together via an edge
*/
void Graph::connect_existing(string from, string to){
    //check if the two nodes exist
    if (!(vertex_collection[from])){
        vertex_collection.erase(from);
        cout << "Error, could not find " << from << "\n";
        return;
    }

    if (!(vertex_collection[to])){
        vertex_collection.erase(to);
        cout << "Error, could not find " << to << "\n";
        return;
    }

    //check if the connections are full
    if (vertex_collection[from]->connections_used == vertex_collection[from]->connections_count){
        cout << "Error, max connections reached on " << from << "\n";
        return;
    }

    if (vertex_collection[to]->connections_used == vertex_collection[to]->connections_count){
        cout << "Error, max connections reached on " << to << "\n";
        return;
    }

    //connect the two nodes
    vertex_collection[from]->connections[vertex_collection[from]->connections_used] = vertex_collection[to];
    vertex_collection[from]->connections_used++;
}

/*
Method Name: display_Graph
Method Description: Displays the connections in the graph
*/
void Graph::display_Graph(){
    for (auto it = vertex_collection.begin(); it != vertex_collection.end(); it++)
    {
        int count = it->second->connections_used;
        if (count == 0)
            cout << it->first;
        else
            cout << it->first << " -> ";

        for (int i = 0; i < count; i++){
            if (i == count-1)
                cout << it->second->connections[i]->name;
            else
                cout << it->second->connections[i]->name << " -> ";
        }
        cout << "\n";
    }
}

/*
Method Name: Get_Vertex
Method Description: Gets the memory location of a vertex in the graph by name
*/
vertex* Graph::Get_Vertex(string name){
    //if vertex does not exist
    if (!(vertex_collection[name])){
        cout << "Error" << "\n";
        return nullptr;
    //return the vertex address
    } else {
        return vertex_collection[name];
    }
}
