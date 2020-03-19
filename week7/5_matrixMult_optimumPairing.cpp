// Optimum pairing for matrix chain multiplication

#include <bits/stdc++.h>
using namespace std;

struct matDim
{
    int nR, nC;
};

void
print(vector<vector<int>>& M)
{
    printf("\n");

    int m = M.size();
    int n = M[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%4d ", M[i][j]);
        printf("\n");
    }

    printf("\n");
}

void
MMC(vector<matDim>& Mat)
{
    int r, c, k, n, inf = 0;

    n = Mat.size();

    for (int i = 1; i < n-1; ++i)
        inf += Mat[i].nR * Mat[i].nC * Mat[i+1].nC;
    inf += 1;

    vector<int> row(n, 0);
    vector<vector<int>> MMC(n, row);
    row.clear();

    print(MMC);

    for (r = 0; r < n; ++r)
        MMC[r][r] = 0;
    
    print(MMC);

    int subprob;
    for (c = 1; c < n; ++c) {
        for (r = c - 1; r >= 0; --r) {
            MMC[r][c] = inf;
            for (k = r; k < c; ++k) {
                subprob = MMC[r][k] + MMC[k+1][c] +
                          (Mat[r].nR * Mat[k].nC * Mat[c].nC);
                if (subprob < MMC[r][c])
                    MMC[r][c] = subprob;
            }
        }
    }

    print(MMC);
}

int
main()
{
    int n, nR, nC;
    vector<matDim> Mat;

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &nR, &nC);
        if (i != 0 && Mat[i - 1].nC != nR) {
            throw invalid_argument("Incompatible matrix dimension");
            return 1;
        }
        Mat.push_back({ nR, nC });
    }

    MMC(Mat);
}