#ifndef V_H
#define V_H

class vertex {
public:
    int cost = 0;
    string name = "";
    vertex** connections = nullptr;
    int connections_count = 0;
    int connections_used = 0;
    int special_case = 0;
};

#endif