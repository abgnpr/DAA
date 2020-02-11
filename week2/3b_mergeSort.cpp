// MERGE SORT

#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> int_v;

/* Merge A[0 .. m-1] & B[0 .. n-1]
 * into C[0 .. m+n-1  */
int_v merge(const int_v &A, const int_v &B) {

    // Current positions in A and B resp.
    int i = 0, j = 0;
    int m = A.size(), n = B.size();

    int_v C;

    while (i + j < m + n) {
        if (i < m && j < n) {
            if (A.at(i) <= B.at(j)) {
                C.push_back(A.at(i));
                i++;
            } else if (A.at(i) > B.at(j)) {
                C.push_back(B.at(j));
                j++;
            }
        } else if (i < m) {
            C.push_back(A.at(i));
            i++;
        } else if (j < n) {
            C.push_back(B.at(j));
            j++;
        }
    }

    return C;
}

/* returns the sorted segment A[left .. . right-1] */
int_v mergeSort(const int_v &A, int left, int right) {

    int_v sorted_A;

    // base case
    if (right - left == 1)
        sorted_A.push_back(A.at(left));

    else if (right - left > 1) {
        int mid = (left + right) / 2;
        int_v L = mergeSort(A, left, mid);
        int_v R = mergeSort(A, mid, right);
        sorted_A =  merge(L, R);
    }

    return sorted_A;
}

int main() {

    int_v A = {43, 32, 22, 78, 63, 57, 91, 13};

    int_v sorted_A = mergeSort(A, 0, A.size());

    cout << "\n";
    for (int i : sorted_A)
        cout << i << "  ";
    cout << "\n\n";

    return EXIT_SUCCESS;
}