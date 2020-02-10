#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> int_v;

// MERGE VARIATIONS

int_v merge_simple(int_v A, int_v B) {

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

int_v merge_noDuplicates(int_v A, int_v B) {

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
      if (A.at(i) != C.back)
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

void print_vec(int_v V) {
  for (int i = 0; i < V.size(); ++i)
    cout << "| " << V.at(i) << " ";
  cout << "|\n";
}

int main() {

  int_v A = {2, 8, 8, 8}, B = {1, 4, 8, 8};
  int_v C = merge_simple(A, B);
  int_v D = merge_noDuplicates(A, B);

  cout << "\n";
  print_vec(C);
  cout << "\n";
  print_vec(D);
  cout << "\n";
  return 0;
}