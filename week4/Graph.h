/*

A data structure to store graphs using
an adjacency list.

### v2 ###

*/

#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

class dest_nd_weight_pair {
    public: 
    int dest_v, w;
    bool operator<(const dest_nd_weight_pair &right) const {
        return this->dest_v < right.dest_v;
    }
};

typedef set<dest_nd_weight_pair> dest_list_with_weight;
typedef map<int, dest_list_with_weight> adj_list;
struct Edge {
    int v1, v2, w;
};
typedef vector<Edge> Edges;

class Graph {

  private:
    adj_list AL;       // adjacency list
    bool isUndirected; // type

    void put_EdgeAndWeight_InAdjList(int v1, int v2, int w) {
        if (v1 == v2)
            return; // self-loops (not allowed)
        auto key = AL.find(v1);
        if (key != AL.end()) // v1 already in list
            key->second.insert({v2, w});
        else { // create new if v1 not in list
            dest_list_with_weight D;
            D.insert({v2, w});
            AL.insert({v1, D});
        }
    }

    void putVertex_InAdjList(int v) {
        auto key = AL.find(v);
        if (key == AL.end()) {
            dest_list_with_weight D;
            AL.insert({v, D});
        }
    }

    void refresh() {
        int vertex;
        dest_list_with_weight neighbours;

        for (auto li : AL) {
            vertex = li.first;
            neighbours = li.second;
            for (dest_nd_weight_pair k : neighbours)
                if (isUndirected)
                    put_EdgeAndWeight_InAdjList(k.dest_v, vertex, k.w);
                else
                    putVertex_InAdjList(k.dest_v);
        }

        // update the vertex set
        set<int> U;
        for (auto li : AL)
            U.insert(li.first);
        Graph::V = U;
    }

  public:
    Graph() { isUndirected = true; }

    set<int> V; // VERTEX SET
    // set<pair<int,int>> E; // EDGE SET

    void add(int v1, int v2, int w) {
        put_EdgeAndWeight_InAdjList(v1, v2, w);
        refresh();
    }

    void add(int v) {
        putVertex_InAdjList(v);
        refresh();
    }

    void add(Edges E) {
        for (Edge e : E)
            put_EdgeAndWeight_InAdjList(e.v1, e.v2, e.w);
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
                    cout << j.dest_v << " ";
            cout << "\n";
        }
        cout << "\n";
    }
    
    void print_AdjList_withWeight() {
        cout << "\nAdjacency List\n";
        for (const auto i : AL) {
            cout << "[" << i.first << "] : ";
            if (i.second.empty())
                cout << "(no out)";
            else
                for (auto j : i.second)
                    cout << j.dest_v << "(" << j.w << ") ";
            cout << "\n";
        }
        cout << "\n";
    }

    adj_list get_adjList() { return AL; }
};