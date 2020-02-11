/*

 * Quicksort
 * Strategy : Start from one end and seep
 * till we claim all the elements.

*/

#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> int_v;

void swap(int_v &V, int pos_x, int pos_y) {
    int temp = V.at(pos_x);
    V.at(pos_x) = V.at(pos_y);
    V.at(pos_y) = temp;
}

void quickSort(int_v &A, int l, int r) {
    if (r - l <= 1)
        return;

    // Partition w.r.t. pivot, a[l]
    int pivot = l, yellow = l + 1;
    for (int green = l + 1; green < r; ++green)
        if (A.at(green) <= A.at(pivot)) {
            swap(A, yellow, green);
            yellow += 1;
        }

    // Move pivot into place
    
}