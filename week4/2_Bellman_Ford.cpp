/*

 * Bellman-Ford Algorithm
 * Finding the shortest path

*/

#include "adjList.h"
using namespace std;

// int min(int &a, int &b) { return (a <= b) ? a : b; }

void BellmanFord(const adj_list &AL, int startVertex) {
    int n = AL.size(), inf = 0;
    map<int, int> Distance;

    for (const auto &li : AL)
        for (const auto &[v, w] : li.second)
            if (w > 0) inf += w;
    inf += 1;

    auto it = AL.begin();   
    for (int i = 1; i <= n; ++i, it++)
        Distance.insert({it->first, inf});

    Distance[startVertex] = 0;

    for (int i = 1; i <= n + 1; ++i)
        for (auto &[u, DL] : AL)
            for (auto &[v, w] : DL)
                Distance[v] = min(Distance[v], Distance[u] + w);
}

int main() {

    adj_list AL;

    addMany(AL, {
                    {1, 2, 10},
                    {3, 2, 1},
                    {3, 4, 1},
                    {4, 5, 3},
                    {5, 6, -1},
                    {7, 6, -1},
                    {8, 7, 1},
                    {1, 8, 8},
                    {7, 2, -4},
                    {2, 6, 2},
                    {6, 3, -2},
                });

    int startVertex = 1;

    BellmanFord(AL, startVertex);

    return EXIT_SUCCESS;
}