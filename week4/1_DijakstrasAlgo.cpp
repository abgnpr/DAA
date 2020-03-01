/*

 * Dijkstra's Algorithm
 * Finding the shortest path.

*/

#include "Graph.h"
#include <iostream>
#include <map>
using namespace std;

bool anotherUnburnt(map<int, int> burnt, int &fistUnburntVertex) {
    for (auto li : burnt)
        if (!li.second) { // if not burnt
            fistUnburntVertex = li.first;
            return true;
            // an unburnt vertex found
        }
    return false;
}

void shortestPath (Graph G, int sourceVertex) {

    map<int, int>
        burnt, // lsit of burnt vertices
        EBT; // Estimated Burn Time

    adj_list AL = G.get_adjList();

    int sumOf_weights = 0;
    for (auto i : AL)
        for (auto j : i.second)
            sumOf_weights += j.w;
    sumOf_weights++;

    for (int v : G.V) {
        burnt.insert({v, 0});
        EBT.insert({v, sumOf_weights /* infinity */});
    }

    EBT[sourceVertex] = 0;

    // choose u : u is burnt and EBT(u) in minimum
    int u;
    while (anotherUnburnt(burnt, u)) {
        // find the unburnt vertex with least distance
        for (int ver : G.V)
            if (EBT[ver] < EBT[u] && !burnt[ver])
                u = ver;

        burnt[u] = 1;

        // recompute expected burn time for each neighbour of u
        for (dest_nd_weight_pair k : AL[u]) {
            int v = k.dest_v;
            int w = k.w; // weight of edge (u,v)
            if (!burnt[v] && EBT[v] > EBT[u] + w)
                EBT[v] = EBT[u] + w;
        }
    }
}

int main() {

    Graph G;

    G.add({ // edges with weights
        {1, 2, 10},
        {1, 3, 80},
        {2, 3, 6 },
        {3, 4, 70},
        {2, 5, 20},
        {5, 7, 10},
        {5, 6, 50},
        {6, 7, 5},
    });

    G.print_AdjList_withWeight();

    shortestPath(G, 1);

    return EXIT_SUCCESS;
}