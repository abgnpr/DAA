// implementing heap using a binary tree

#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

typedef vector<int> intv;

struct heap {
    intv tree, nodeToHeap, heapToNode;
};

void heap_fix() {}

void swap(intv &V, int x, int y) {
    int temp = V[x];
    V[x] = V[y];
    V[y] = temp;
}

void fixDown(heap &H, int i) {
    if (H.tree[i] < H.tree[2 * i + 1])
        swap(H.tree, i, 2 * i + 1);
    if (H.tree[i] < H.tree[2 * i + 2])
        swap(H.tree, i, 2 * i + 2);
}

heap heapify(intv V) {
    heap H;
    H.tree = V;
    int nLevels, first, last;

    nLevels = (int)log2(H.tree.size());

    for (int k = nLevels - 1; k >= 0; --k) {

        if (k == 0)
            first = last = 0;
        else {
            first = (int)pow(2, k - 1) + 1;
            last = (int)pow(2, k);
        }

        for (int j = first; j <= last; ++j)
            fixDown(H, j);
    }
}

void insert(const heap &H, int n) {}

void delete_max(const heap &H) {}

void update(const heap &H, int node, int val) {}

void print(heap const &H) {
    int n = H.tree.size();
    int nLevels = (int)log2(n) + 1;
    for (int i = 0, j = nLevels; i < n; ++i, --j) {
        for (int k = 1; k <= j; ++k)
            cout << " ";
    }
}

int main() {}