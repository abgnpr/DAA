#include <map>
#include <set>
#include <vector>
using namespace std;

#define UNDIRECTED 0

struct vw_pair {
    int v;
    int w;
};

bool operator<(const vw_pair &a, const vw_pair &b) {
    return a.v < b.v ? true : false;
}

struct uvw_triplet {
    int u;
    int v;
    int w;
};

typedef set<vw_pair> destList_withWt;
typedef map<int, destList_withWt> adj_list;
typedef set<int> vertexSet;

void add_EdgeAndWeight_InAdjList(adj_list &AL, int v1, int v2, int w) {
    if (v1 == v2)
        return; // self-loops (not allowed)
    auto key = AL.find(v1);
    if (key != AL.end()) // v1 already in list
        key->second.insert({v2, w});
    else { // create new if v1 not in list
        destList_withWt D;
        D.insert({v2, w});
        AL.insert({v1, D});
    }
    if (UNDIRECTED) {
        key = AL.find(v2);
        if (key != AL.end())
            key->second.insert({v1, w});
        else {
            destList_withWt D;
            D.insert({v1, w});
            AL.insert({v2, D});
        }
    }
}

void putVertex_InAdjList(adj_list &AL, int v) {
    auto key = AL.find(v);
    if (key == AL.end()) {
        destList_withWt D;
        AL.insert({v, D});
    }
}

void addMany(adj_list &AL, vector<uvw_triplet> triplets) {
    for (uvw_triplet t : triplets) {
        add_EdgeAndWeight_InAdjList(AL, t.u, t.v, t.w);
    }
}

vertexSet get_vertexSet(const adj_list &AL) {
    vertexSet V;
    for (auto it = AL.begin(); it != AL.end(); ++it)
        V.insert(it->first);
    return V;
}

int weight(const adj_list &AL, int i, int j) {}