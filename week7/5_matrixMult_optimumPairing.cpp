// Optimum pairing for matrix chain multiplication

#include <bits/stdc++.h>
using namespace std;

void
print(vector<vector<int>>&);

void
MMC(vector<int>&);

int
main()
{
    vector<int> P{ 5, 4, 7, 2, 3 };
    MMC(P);
}

void
MMC(vector<int>& P)
{
    int pn = P.size(), inf = 0;

    for (int i = 0; i <= pn - 3; ++i)
        inf += P[i] * P[i + 1] * P[i + 2];
    inf += 1;

    int n = pn - 1; // n matrics
    vector<int> row(n, 0);
    vector<vector<int>> MMC(n, row);
    row.clear();
    // for (int r = 0; r < n-1; ++r)
    //     MMC[r][r] = 0;

    print(MMC);

    int subprob;
    for (int c = 1; c < n; ++c) {
        for (int r = c - 1; r >= 0; --r) {
            MMC[r][c] = inf;
            for (int k = r; k < c; ++k) {
                subprob = MMC[r][k] + MMC[k + 1][c] +
                          (P.at(k) * P.at(k + 1) * P.at(c + 1));
                if (subprob < MMC[r][c])
                    MMC[r][c] = subprob;
                print(MMC);
            }
        }
    }

    print(MMC);
}

void
print(vector<vector<int>>& M)
{
    printf("\n");

    int m = M.size();
    int n = M[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            if (i <= j)
                printf("%4d ", M[i][j]);
            else
                printf("     ");
        printf("\n\n");
    }

    printf("\n");
}
