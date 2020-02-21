/*

 * BFS using a graph stucture employing an
 * adjacency list.

 * Checking connectivity
 * Identifying a path
 * Recording distance (steps)

*/

#include "Graph.h"
#include <iostream>
#include <map>
#include <queue>

bool BFS(Graph G, int startVertex, int endvertex) {

    map<int, bool> vistingRecord;
    #define VISITED true
    #define NOT_VISITED false

    queue<int> vertices_toBeExplored;

    map<int, int> levels, parents;
    #define NOT_DEFINED -1

    for (const int vertex : G.V) {
        vistingRecord.insert({vertex, NOT_VISITED});
        levels.insert({vertex, NOT_DEFINED});
        parents.insert({vertex, NOT_DEFINED});
    }

    vistingRecord.at(startVertex) = VISITED;
    vertices_toBeExplored.push(startVertex);

    adj_list AL = G.get_adjList();

    int vertex_beingExplored;
    dest_list neighbours;

    levels.at(startVertex) = 0;
    while (!vertices_toBeExplored.empty()) {
        vertex_beingExplored = vertices_toBeExplored.front();
        neighbours = AL.at(vertex_beingExplored);
        for (int neighbour : neighbours)
            if (vistingRecord.at(neighbour) == NOT_VISITED) {
                vistingRecord.at(neighbour) = VISITED;
                vertices_toBeExplored.push(neighbour);
                parents.at(neighbour) = vertex_beingExplored;
                levels.at(neighbour) = levels.at(vertex_beingExplored)+1;
            }
        vertices_toBeExplored.pop();
    }

    cout << "\nV  L  P\n";
    for (int v : G.V)
        cout << v << "  " << levels.at(v) << "  " << parents.at(v) << "\n";
    cout << "\n";

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

    // G.print_AdjList();

    return EXIT_SUCCESS;
}
