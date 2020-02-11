/*

 * Quicksort
 * Strategy : Start from one end and sweep
 * till we claim all the elements.

*/

#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> int_v;

/* swap elements at pos_x and pos_y in vector V */
void swap(int_v &V, int pos_x, int pos_y) {
    int temp = V.at(pos_x);
    V.at(pos_x) = V.at(pos_y);
    V.at(pos_y) = temp;
}

/* Sort A[l .. r-1] */
void quickSort(int_v &A, int l, int r) {

    // base case
    if (r - l <= 1)
        return;

    int green, yellow, pivot;

    // Partition w.r.t. pivot, a[l]
    pivot = l;
    yellow = pivot + 1;
    for (int green = l + 1; green < r; ++green)
        if (A.at(green) <= A.at(pivot)) {
            swap(A, yellow, green);
            yellow += 1;
        }

    // Move pivot into place
    swap(A, pivot, yellow - 1);
    pivot = yellow - 1;

    // recursive calls on the
    // left and right parts
    quickSort(A, l, pivot + 1); // from l to pivot
    quickSort(A, pivot + 1, r); // from pivot+1 to r
}

/* driver code */
int main() {

    int_v A = {43, 32, 22, 78, 63, 57, 91, 13};
    quickSort(A, 0, A.size());

    if (!A.empty()) {
        cout << "\n";
        for (int i : A)
            cout << "| " << i << " ";
        cout << "|";
        cout << "\n\n";

    } else {
        cout << "\nA is empty\n\n";
    }
}