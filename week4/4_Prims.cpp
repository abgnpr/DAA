#include "adjList.h"
#include <bits/stdc++.h>
using namespace std;

typedef map<int, int> intmap;
typedef set<int> intset;
struct edge { int u,v; };

int unvisited_u_withMinDist(intmap &Dist, intset &unvisited) {
    int u_minDist = unvisited.begin;
    for (int u : unvisited)
        if (Dist[u] < Dist[u_minDist]) u_minDist = u;
    unvisited.erase(u_minDist);
    return u_minDist;
}

void Prim(const adj_list &AL) {

    intmap Nbr_TV, Dist_TV;
    intset visited, unvisited;
    vector<edge> TE;

    int inf = 0;

    for (const auto &[v, DL] : AL)
        for (auto &[v, w] : DL)
            inf += w;

    for (const auto &[v, DL] : AL) {
        unvisited.insert(v);
        Nbr_TV.insert({v, -1});
        Dist_TV.insert({v, inf});
    }

    
    int root = AL.begin()->first;

    unvisited.erase(root);
    visited.insert(root);

    for (const auto &[v, w] : AL.at(root)) {
        Nbr_TV[v] = root;
        Dist_TV[v] = w;
    }

    for (int i = 2; i <= AL.size(); ++i) {
        int u = unvisited_u_withMinDist(Dist_TV, unvisited);
        visited.insert(u);
        TE.push_back({u, Nbr_TV[u]});
        for (auto &[v,w] : AL.at(u)) {
            if (unvisited.find(v) != unvisited.end()) {
                if (Dist_TV[v] > w) {
                    Dist_TV[v] = w;
                    Nbr_TV
                    /* 
                    ***** HEAP REQUIRED ******
                     */
                }
            }
        }
    }

}

int main() {

    adj_list AL;
    addMany(AL, {
                    {1, 3, 18},
                    {1, 2, 10},
                    {3, 4, 70},
                    {3, 2, 6},
                    {2, 5, 20},
                    {4, 5, 8},
                });

    return EXIT_SUCCESS;
}