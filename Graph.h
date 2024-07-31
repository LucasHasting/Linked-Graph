#ifndef G_H
#define G_H

#include <map>
#include "vertex.h"
using namespace std;

class Graph{
private:
    map<string, vertex*> vertex_collection;

public:
    Graph(string name, int connections, int cost = 0);
    ~Graph();
    void Add_Vertex(string from, string name, int connections, bool bidirectional = false, int cost = 0);
    void connect_existing(string from, string to);
    void display_Graph();
    vertex* Get_Vertex(string name);
};

#endif