/*

 * DFS with numbering

*/

#include "Graph.h"
#include <cstdio>
#include <map>
#include <stack>
using namespace std;

void DFS(Graph G, const int startVertex, const int endVertex) {

    struct s {
        int v, k;
    };
    map<int, int> visited, parents, pre, post;
    stack<s> suspended;
    adj_list AL;
    int v, k, count = 0;

    AL = G.get_adjList();
    for (int v : G.V) {
        visited.insert({v, 0});
        parents.insert({v, -1});
        pre.insert({v, 0});
        post.insert({v, 0});
    }

    suspended.push({startVertex, 0});
    visited[startVertex] = 1;

    pre[startVertex] = count++;
    while (!suspended.empty()) {
        v = suspended.top().v;
        k = suspended.top().k;
        suspended.pop();
        while (k < AL[v].size()) {
            auto n = AL[v].cbegin();
            for (int i = 0; i < k; ++i, n++)
                ;
            if (!visited[*n]) {
                visited[*n] = 1;
                parents[*n] = v;
                suspended.push({v, k + 1});
                v = *n;
                k = 0;
                pre[v] = count++;
            } else
                k++;
        }
        post[v] = count++;
    }

    printf("\nReachable : ");
    visited[endVertex] ? printf("YES\n") : printf("NO\n");
    printf("\nvertex\tparent\tvisited\t\tPre\tPost\n");
    for (int v : G.V)
        printf("%2d\t%2d\t%2d\t\t%3d\t%3d\n", v, parents[v], visited[v], pre[v],
               post[v]);
    printf("\n");
}

int main() {

    Graph G;

    // add edges
    // G.add({
    //     {1, 2}, {1, 3}, {1, 4}, {2, 3}, {4, 5}, {4, 8}, {5, 6}, 
    //     {5, 7}, {6, 7}, {6, 8}, {6, 9}, {8, 9}, {9, 1}
    // });

    G.add({
        {1, 2}, {1, 3}, {1, 6}, {2, 5}, {3, 4}, 
        {4, 1}, {4, 8}, {5, 2}, {5, 6}, {5, 7},
        {6, 7}, {6, 2}, {5, 8}, {8, 7}  
    });

    int startVertex, endVertex;
    printf("\nstartVertex  :  ");
    scanf("%d", &startVertex);
    printf("endVertex    :  ");
    scanf("%d", &endVertex);

    DFS(G, startVertex, endVertex);

    return EXIT_SUCCESS;
}