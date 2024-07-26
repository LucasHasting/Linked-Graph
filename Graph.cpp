#include <map>
#include <iostream>
using namespace std;

class vertex {
public:
    int cost = 0;
    string name = "";
    vertex** connections = nullptr;
    int connections_count = 0;
    int connections_used = 0;
    int special_case = 0;
};

class Graph{
private:
    map<string, vertex*> vertex_collection;

public:
    Graph(string name, int connections, int cost = 0){
        vertex_collection[name] = new vertex;
        vertex_collection[name]->cost = cost;
        vertex_collection[name]->name = name;
        vertex_collection[name]->connections_count = connections;
        vertex_collection[name]->connections = new vertex*[connections];
    }

    ~Graph(){
        for (auto it = vertex_collection.begin(); it != vertex_collection.end(); it++)
        {
            delete vertex_collection[it->first];
            delete [] it->second->connections;
        }
    }

    void Add_Vertex(string from, string name, int connections, bool bidirectional = false, int cost = 0){
        //check if from exist
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

        vertex_collection[name] = new vertex;
        vertex_collection[name]->cost = cost;
        vertex_collection[name]->name = name;
        vertex_collection[name]->connections_count = connections;
        vertex_collection[name]->connections = new vertex*[connections];
        vertex_collection[from]->connections[vertex_collection[from]->connections_used] = vertex_collection[name];
        vertex_collection[from]->connections_used++;

        if (bidirectional){
            vertex_collection[name]->connections[vertex_collection[name]->connections_used] = vertex_collection[from];
            vertex_collection[name]->connections_used++;
        }
    }

    void connect_existing(string from, string to){
        //check if they exist
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

        vertex_collection[from]->connections[vertex_collection[from]->connections_used] = vertex_collection[to];
        vertex_collection[from]->connections_used++;
    }

    vertex* Get_Vertex(string name){
        if (!(vertex_collection[name])){
            cout << "Error" << "\n";
            return nullptr;
        } else {
            return vertex_collection[name];
        }
    }

    void display_Graph(){
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

};
