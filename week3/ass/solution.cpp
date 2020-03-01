/*
 * BFS on cities:
 * marks cities reachable from `startVertex` as visited
 * returns total number of museums visited during search
 */

#include <bits/stdc++.h>
using namespace std;

typedef set<int> dest_list;
typedef map<int, dest_list> adj_list;
typedef map<int, int> intmap;

int BFS(const adj_list &AL, int startVertex, set<int> &visited, const intmap &museums) {
    int n_MuseumVisited = 0;
    queue<int> vertices_toBeExplored;

    visited.erase(startVertex);
    n_MuseumVisited += museums.at(startVertex);
    vertices_toBeExplored.push(startVertex);

    while (!vertices_toBeExplored.empty()) {
        int v = vertices_toBeExplored.front();
        for (int neighbour : AL.at(v))
            if (visited.find(neighbour) != visited.end()) {
                // visited[neighbour] = 1;
                visited.erase(neighbour);
                n_MuseumVisited += museums.at(neighbour);
                vertices_toBeExplored.push(neighbour);
            }
        vertices_toBeExplored.pop();
    }

    return n_MuseumVisited;
}

typedef deque<int> dq_int;
dq_int merge(const dq_int &A, const dq_int &B) {
    int i = 0;
    int j = 0;
    int m = A.size(), n = B.size();
    dq_int C;
    while (i + j < m + n) {
        if (j == n)
            C.push_back(A.at(i++));
        else if (i == m)
            C.push_back(B.at(j++));
        else {
            if (A.at(i) <= B.at(j))
                C.push_back(A.at(i++));
            else if (A.at(i) > B.at(j))
                C.push_back(B.at(j++));
        }
    }
    return C;
}
dq_int mergesort(const dq_int &A, int left, int right) {
    dq_int sorted_A;
    if (right - left == 1)
        sorted_A.push_back(A.at(left));
    else if (right - left > 1) {
        int mid = (left + right) / 2;
        dq_int L = mergesort(A, left, mid);
        dq_int R = mergesort(A, mid, right);
        sorted_A = merge(L, R);
    }
    return sorted_A;
}

int main() {

    int N,      // number of cities
        M,      // number of roads
        K,      // number of months
        ui, vi; // road from ui to vi

    adj_list AL;

    // input N, M, K
    scanf("%d %d %d", &N, &M, &K);

    // input roads
    for (int i = 1; i <= M; ++i) {
        scanf("%d %d", &ui, &vi);
        // G.add(ui, vi);
        auto key = AL.find(ui);
        if (key != AL.end())
            key->second.insert(vi);
        else {
            dest_list D;
            D.insert(vi);
            AL.insert({ui, D});
        }
        key = AL.find(vi);
        if (key != AL.end())
            key->second.insert(ui);
        else {
            dest_list D;
            D.insert(ui);
            AL.insert({vi, D});
        }
    }

    intmap museums;
    set<int> visited;
    
    int n;
    for (int i = 1; i <= N; ++i) {
        if (AL.find(i) == AL.end()) {
            auto key = AL.find(i);
            if (key == AL.end()) {
                dest_list D;
                AL.insert({i, D});
            }
        }
        scanf("%d", &n);
        museums.insert({i, n});
        visited.insert(i);
    }

    deque<int> totalMus_in_comps;
    while (!visited.empty())
        totalMus_in_comps.push_back(BFS(AL, *visited.begin(), visited, museums));

    // sort the above list
    totalMus_in_comps =
        mergesort(totalMus_in_comps, 0, totalMus_in_comps.size());

    int TMV = 0; // total museums visited

    for (int k = 1; k <= K; ++k) {
        if (totalMus_in_comps.empty()) {
            TMV = -1;
            break;
        }
        if (k % 2) {
            TMV += totalMus_in_comps.back();
            totalMus_in_comps.pop_back();
        } else {
            TMV += totalMus_in_comps.front();
            totalMus_in_comps.pop_front();
        }
    }

    printf("%d\n", TMV);
    return EXIT_SUCCESS;
}