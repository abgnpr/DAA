#include <bits/stdc++.h>
using namespace std;

typedef list <list<int>> list_of_list;

struct graph
{
    set<int> V;             // VERTEX SET
    set<pair<int,int>> E;   // EDGE SET
};


/* BFS starting from vertex i */
bool BFS(graph G, int startVertex, int endVertex) {

    map<int,bool> vistingRecord;
    #define VISITED true
    #define NOT_VISITED false

    // Initialization
    for (auto vertex : G.V)
        vistingRecord.insert({vertex, NOT_VISITED});

    /* Vertices that have been visited but
     * not yet explored */
    queue<int> vertices_toBeExplored;

    // Start the exploration at `startVertex`
    vistingRecord.at(startVertex) = VISITED;
    vertices_toBeExplored.push(startVertex);

    // Explore each vertex in Q
    while (!vertices_toBeExplored.empty()) {
        for (auto edge : G.E) {
            int v1 = edge.first, v2 = edge.second;
            if (vertices_toBeExplored.front() == v1  &&
                vistingRecord.at(v2) == NOT_VISITED) {
                vistingRecord.at(v2) = VISITED;
                vertices_toBeExplored.push(v2);
            }
        }
        vertices_toBeExplored.pop();
    }

    return vistingRecord.at(endVertex);

}

/* driver code */
int main() {

    graph mapOfIndia;

    // vertex set
    mapOfIndia.V = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // edge set
    mapOfIndia.E = {
        {1, 2}, {1, 3}, {1, 4}, {2, 3}, {4, 5}, {4, 8}, {5, 6},
        {5, 7}, {6, 7}, {6, 8}, {6, 9}, {8, 9}, {9, 10}
    };

    BFS(mapOfIndia, 1, 10)? cout << "YES" : cout << "NO";
    cout << "\n";

    // // adjacency list
    // list_of_list adj_list = {
    //     {1, 2, 3},
    //     {1, 3},
    //     {1, 2},
    //     {1, 5, 8},
    //     {4, 6, 7},
    //     {5, 7, 8, 9},
    //     {5, 6},
    //     {4, 6, 9},
    //     {6, 8, 10},
    //     { 9 },
    // };

    // for (auto vertex : adj_list) {
    //     for(auto neighbours : vertex)
    //         cout << neighbours << " ";
    //     cout << "\n";
    // }

    return EXIT_SUCCESS;
}