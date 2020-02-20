/*

Moving intervals

hint :
sort the intervals and check for overlaps

 */

#include <iostream>
#include <vector>
using namespace std;

struct interval {
    long S;
    long E;
};

typedef vector<interval> voi;

voi merge(const voi &A, const voi &B) {
    int i = 0;
    int j = 0;
    int m = A.size(), n = B.size();

    voi C;

    while (i + j < m + n) {
        if (j == n)
            C.push_back(A.at(i++));
        else if (i == m)
            C.push_back(B.at(j++));
        else {
            if (A.at(i).S <= B.at(j).S)
                C.push_back(A.at(i++));
            else if (A.at(i).S > B.at(j).S)
                C.push_back(B.at(j++));
        }
    }

    return C;
}

voi mergesort(const voi &A, int left, int right) {
    voi sorted_A;
    if (right - left == 1)
        sorted_A.push_back(A.at(left));

    else if (right - left > 1) {
        int mid = (left + right) / 2;
        voi L = mergesort(A, left, mid);
        voi R = mergesort(A, mid, right);
        sorted_A = merge(L, R);
    }

    return sorted_A;
}

/* return conflictLoc if conflict found else returns -1 */
int lookForConflicts(const voi &intervals) {
    for (int i = 0; i < intervals.size() - 1; ++i)
        if (intervals.at(i + 1).S >= intervals.at(i).S &&
            intervals.at(i + 1).S <= intervals.at(i).E) {
            return i;
        }
    return -1;
}

/* sets the badflag : success - 0; failure - 1  */
int persuade(voi intervals, int i, long C) {
    long diff, E, S;
    diff = intervals.at(i).E - intervals.at(i).S + 1;
    intervals.erase(intervals.begin() + i);
    intervals.push_back({C + 1, 0});
    E = 0, S;
    for (interval i : intervals) {
        S = i.S;
        if (S - E - 1 >= diff) {
            if (lookForConflicts(intervals) == -1)
                return 0;
            else
                return 1;
        }
        E = i.E;
    }
    return 1;
}

int main() {

    long C, Si, Ei;
    int N, K, i;

    cin >> C >> N >> K;

    voi intervals;
    for (i = 1; i <= N; ++i) {
        cin >> Si >> Ei;
        intervals.push_back({Si, Ei});
    }

    intervals = mergesort(intervals, 0, intervals.size());

    int badflag = 0;

    int overlapping_i = lookForConflicts(intervals);

    if (overlapping_i >= 0) {
        badflag = 1;
        if (K) {
            badflag = persuade(intervals, overlapping_i, C);
            if (badflag)
                badflag = persuade(intervals, overlapping_i + 1, C);
        }
    }

    badflag ? cout << "Bad\n" : cout << "Good\n";

    return EXIT_SUCCESS;
}