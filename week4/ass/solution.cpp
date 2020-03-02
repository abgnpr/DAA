// Padayatra

#include <bits/stdc++.h>
using namespace std;

#define UNDIRECTED 1

struct vw_pair {
    int v, w;
};

typedef set<vw_pair> destList_withWt;
typedef map<int, destList_withWt> adj_list;
typedef set<int> vertexSet;

bool operator<(const vw_pair &a, const vw_pair &b) {
    return a.v < b.v ? true : false;
}

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

void removeEdge_fromAdjList(adj_list &AL, int v1, int v2) {

    for (auto it = AL.at(v1).begin(); it != AL.at(v1).end(); ++it)
        if (it->v == v2) {
            AL.at(v1).erase(it);
            break;
        }

    if (UNDIRECTED)
        for (auto it = AL.at(v2).begin(); it != AL.at(v2).end(); ++it)
            if (it->v == v1) {
                AL.at(v2).erase(it);
                break;
            }
}

void putVertex_InAdjList(adj_list &AL, int v) {
    auto key = AL.find(v);
    if (key == AL.end()) {
        destList_withWt D;
        AL.insert({v, D});
    }
}

vertexSet get_vertexSet(const adj_list &AL) {
    vertexSet V;
    for (auto it = AL.begin(); it != AL.end(); ++it)
        V.insert(it->first);
    return V;
}

/* void print_AdjList_withWeight(const adj_list &AL) {
    cout << "\nAdjacency List\n";
    for (const auto i : AL) {
        cout << "[" << i.first << "] : ";
        if (i.second.empty())
            cout << "(no out)";
        else
            for (auto j : i.second)
                cout << j.v << "(" << j.w << ") ";
        cout << "\n";
    }
    cout << "\n";
} */

bool anotherUnburnt(int burnt[], int size, int &fistUnburntVertex) {
    for (int i = 1; i < size; ++i)
        if (!burnt[i]) {
            fistUnburntVertex = i;
            return true;
        }
    return false;
}

long Dijkstras(const adj_list &AL, int src, int dest) {

    auto last = --AL.end();
    int lastVertex = last->first;

    long EBT[lastVertex + 1]; 
    int burnt[lastVertex + 1];

    vertexSet V = get_vertexSet(AL);

    for (int i = 0; i <= lastVertex; ++i) {
        if (V.find(i) != V.end()) {
            burnt[i] = 0;
        } else
            burnt[i] = 1;

        EBT[i] = INT32_MAX;
    }

    EBT[src] = 0;

    int u;
    while (anotherUnburnt(burnt, lastVertex + 1, u)) {

        for (int i = 1; i < lastVertex + 1; ++i)
            if (!burnt[i] && EBT[i] < EBT[u])
                u = i;

        burnt[u] = 1;

        for (auto k : AL.at(u))
            if (!burnt[k.v] && EBT[u] + k.w < EBT[k.v])
                EBT[k.v] = EBT[u] + k.w;
        
        if (burnt[dest]) return EBT[dest];
    }

    return EBT[dest];
}

int main() {

    int N,                    // number of roads
        S,                    // starting point
        T,                    // ending point
        D;
                            // length of the road
    long SD,                   // shortest distance
        minSD = 0;            // minimum shortest distance
    
    bool minSD_notSet = true; // flag

    adj_list AL, al;

    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d %d %d", &S, &T, &D);
        add_EdgeAndWeight_InAdjList(AL, S, T, D);
    }

    al = AL;

    int u;

    for (auto i : AL) {
        u = i.first;
        for (auto j : i.second) {

            removeEdge_fromAdjList(al, u, j.v);

            SD = Dijkstras(al, j.v, u) + j.w;

            if (minSD_notSet) {
                minSD = SD;
                minSD_notSet = false;
            } else if (SD < minSD)
                minSD = SD;

            add_EdgeAndWeight_InAdjList(al, u, j.v, j.w);
        }
    }

    printf("%ld\n", minSD);
    return EXIT_SUCCESS;
}