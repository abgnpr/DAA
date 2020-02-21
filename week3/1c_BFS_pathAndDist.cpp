/*

 * BFS using a graph stucture employing an
 * adjacency list.

 * Checking connectivity
 * Identifying a path
 * Recording distance (steps)

*/

#include "Graph.h"
#include <cstdio>
#include <map>
#include <queue>
#include <stack>

void BFS(Graph G, const int startVertex, const int endVertex) {

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

    int v;
    dest_list neighbours;

    levels.at(startVertex) = 0;
    while (!vertices_toBeExplored.empty()) {
        v = vertices_toBeExplored.front();
        neighbours = AL.at(v);
        for (int neighbour : neighbours)
            if (vistingRecord.at(neighbour) == NOT_VISITED) {
                vistingRecord.at(neighbour) = VISITED;
                vertices_toBeExplored.push(neighbour);
                parents.at(neighbour) = v;
                levels.at(neighbour) = levels.at(v) + 1;
            }
        vertices_toBeExplored.pop();
    }

    // reachability and shortest path
    if (vistingRecord.at(endVertex)) {

        printf("\nReachable : YES\n\n");

        v = endVertex;
        stack<int> path_list;
        do {
            path_list.push(v);
        } while ((v = parents.at(v)) != NOT_DEFINED);

        printf("Path : [%d]", path_list.top());
        path_list.pop();
        while (!path_list.empty()) {
            printf(" -> [%d]", path_list.top());
            path_list.pop();
        }

        printf("\n");
        printf("\nSteps : %d\n", levels.at(endVertex));

    } else
        printf("\nReachable : NO\n");

    printf("\nvertex\tparent\tlevel\tvisited\n");
    for (int v : G.V)
        printf("%2d\t%2d\t%2d\t%2d\n", 
            v, parents.at(v), levels.at(v),vistingRecord.at(v));
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
    G.add(11);

    int startVertex, endVertex;

    printf("\nstartVertex  :  ");
    scanf("%d", &startVertex);
    printf("endVertex    :  ");
    scanf("%d", &endVertex);

    BFS(G, startVertex, endVertex);

    G.print_AdjList();

    return EXIT_SUCCESS;
}
