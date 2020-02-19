#include "Graph.h"
#include <iostream>
#include <queue>
#include <map>

bool BFS(Graph G, int startVertex, int endvertex) {

    /* Vetices that have been visited */
    map<int, bool> vistingRecord;
    #define VISITED true
    #define NOT_VISITED false

    // Initialization
    for (const int vertex : G.V)
        vistingRecord.insert({vertex, NOT_VISITED});

    /* Vertices that have been visited but
     * not yet explored */
    queue<int> vertices_toBeExplored;

    // Start exploration at ``startVertex`
    vistingRecord.at(startVertex) = VISITED;
    vertices_toBeExplored.push(startVertex);

    adj_list AL = G.get_adjList();

    // Explore each vertex in Q
    while (!vertices_toBeExplored.empty()) {
        int vertex_beingExplored = vertices_toBeExplored.front();
        for (int neighbour : AL.at(vertex_beingExplored))
            if (vistingRecord.at(neighbour) == NOT_VISITED) {
                vistingRecord.at(neighbour) = VISITED;
                vertices_toBeExplored.push(neighbour);
            }
        vertices_toBeExplored.pop();
    }

    return vistingRecord.at(endvertex);
}

int main() {

    Graph G;

    // add edges
    G.add(1, 2);
    G.add(1, 3);
    G.add(1, 4);
    G.add(2, 3);
    G.add(4, 5);
    G.add(4, 8);
    G.add(5, 6);
    G.add(5, 7);
    G.add(6, 7);
    G.add(6, 8);
    G.add(6, 9);
    G.add(8, 9);
    G.add(9, 10);

    cout << "\n";
    BFS(G, 1, 10) ? cout << "rechable" : cout << "unreachable";
    cout << "\n";

    G.print_AdjList();

    return EXIT_SUCCESS;
}