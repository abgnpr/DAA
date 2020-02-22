/*

A data structure to store graphs using
an adjacency list.

*/

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

typedef set<int> dest_list;
typedef map<int, dest_list> adj_list;
struct Edge { int v1, v2; };
typedef vector<Edge> Edges;

class Graph {

  private:
    adj_list AL;       // adjacency list
    bool isUndirected; // type

    void putEdgeIn_AdjList(int v1, int v2) {
        if (v1 == v2)
            return; // self-loops (X)
        auto key = AL.find(v1);
        if (key != AL.end())
            key->second.insert(v2);
        else {
            dest_list D;
            if (v2)
                D.insert(v2);
            AL.insert({v1, D});
        }
    }

    void putVertexIn_AdjList(int v) {
        auto key = AL.find(v);
        if (key == AL.end()) {
            dest_list D;
            AL.insert({v, D});
        }
    }

    void refresh() {
        int vertex;
        dest_list neighbours;
        
        for (auto li : AL) {
            vertex = li.first;
            neighbours = li.second;
            for (int neighbour : neighbours)
                if (isUndirected)
                    putEdgeIn_AdjList(neighbour, vertex);
                else
                    putVertexIn_AdjList(neighbour);
        }

        // update the vertex set
        set<int> U;
        for (auto li : AL)
            U.insert(li.first);
        Graph::V = U;
    }

  public:
    Graph() { isUndirected = false; }

    set<int> V; // VERTEX SET
    // set<pair<int,int>> E; // EDGE SET

    void add(int v1, int v2) {
        putEdgeIn_AdjList(v1, v2);
        refresh();
    }

    void add(int v) {
        putVertexIn_AdjList(v);
        refresh();
    }

    void add(Edges E) {
        for (Edge e : E)
            putEdgeIn_AdjList(e.v1, e.v2);
        refresh();
    }

    void print_AdjList() {
        cout << "\nAdjacency List\n";
        for (const auto i : AL) {
            cout << "[" << i.first << "] : ";
            if (i.second.empty())
                cout << "(no out)";
            else
                for (auto j : i.second)
                    cout << j << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    adj_list get_adjList() { return AL; }
};
