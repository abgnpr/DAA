#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> int_v;

// MERGE VARIATIONS

int_v simple_merge(int_v A, int_v B) {

    int i = 0, j = 0, k = 0;
    int m = A.size(), n = B.size();

    int_v C;

    while (i < m && j < n) {
        if (A.at(i) <= B.at(j)) {
            C.push_back(A.at(i));
            i++;
        } else if (A.at(i) > B.at(j)) {
            C.push_back(B.at(j));
            j++;
        }
    }

    while (i < m || j < n) {
        if (i < m) {
            C.push_back(A.at(i));
            i++;
        }
        if (j < n) {
            C.push_back(B.at(j));
            j++;
        }
    }

    return C;
}

/* Union of two unsorted lists */
int_v union_OF(int_v A, int_v B) {

    int i = 0, j = 0, k = 0;
    int m = A.size(), n = B.size();

    int_v C;

    while (i < m && j < n) {
        if (A.at(i) < B.at(j)) {
            C.push_back(A.at(i));
            i++;

        } else if (A.at(i) > B.at(j)) {
            C.push_back(B.at(j));
            j++;

        } else if (A.at(i) == B.at(j)) {
            C.push_back(A.at(i));
            i++;
            j++;
        }
    }

    while (i < m || j < n) {
        if (i < m) {
            if (A.at(i) != C.back())
                C.push_back(A.at(i));
            i++;
        }
        if (j < n) {
            if (B.at(j) != C.back())
                C.push_back(B.at(j));
            j++;
        }
    }

    return C;
}

/* Intersection of two unsorted lists */
int_v intersection_OF(int_v A, int_v B) {

    int i = 0, j = 0, k = 0;
    int m = A.size(), n = B.size();

    int_v C;

    while (i < m && j < n) {
        if (A.at(i) < B.at(j)) {
            i++;

        } else if (A.at(i) > B.at(j)) {
            j++;

        } else if (A.at(i) == B.at(j)) {
            C.push_back(A.at(i));
            i++;
            j++;
        }
    }

    return C;
}

/* Elements present in A, but not in B */
int_v diff(int_v A, int_v B) {

    int i = 0, j = 0;
    int m = A.size(), n = B.size();

    int_v C;

    while (i < m) {
        if (j < n) {

            if (A.at(i) < B.at(j)) {
                C.push_back(A.at(i));
                i++;

            } else if (A.at(i) > B.at(j)) {
                j++;

            } else {
                i++;
                j++;
            }

        } else {
            C.push_back(A.at(i++));
        }
    }

    return C;
}

void print_vec(int_v V) {
    for (int i = 0; i < V.size(); ++i)
        cout << "| " << V.at(i) << " ";
    if (V.size() != 0)
        cout << "|\n";
    else
        cout << "*empty*\n";
}

int main() {

    // int_v A = {1, 2, 3, 4, 8};
    // int_v B = {1, 4, 5, 8};

    int_v A = {1, 3, 5, 7};
    int_v B = {2, 4, 6, 7};

    int_v C = simple_merge(A, B);
    int_v D = union_OF(A, B);
    int_v E = intersection_OF(A, B);
    int_v F = diff(A, B);

    cout << "\n";
    print_vec(C);
    cout << "\n";
    print_vec(D);
    cout << "\n";
    print_vec(E);
    cout << "\n";
    print_vec(F);
    cout << "\n";

    return 0;
}
