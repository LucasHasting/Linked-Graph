#include "Graph.h"

int main(){
    Graph g("street1", 3);
    g.Add_Vertex("street1", "street2", 3, true);
    g.display_Graph();
    return 0;
}
