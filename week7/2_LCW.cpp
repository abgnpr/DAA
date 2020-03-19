// LEAST COMMON SUB-WORD
// -     -         -

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> intv;
typedef vector<vector<int>> intvv;

void
printLCW(intvv LCW)
{
    printf("\n");

    int m = LCW.size();
    int n = LCW[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%d ", LCW[i][j]);
        printf("\n");
    }

    printf("\n");
}

int
LCW(const string wrd1, const string wrd2)
{
    int r, c, m, n, maxLCW;

    m = wrd1.length();
    n = wrd2.length();

    intv row(n + 1, 0);
    intvv LCW(m + 1, row);
    row.clear();

    printLCW(LCW);

    maxLCW = 0;

    for (c = n-1; c >= 0; --c) {
        for (r = m-1; r >= 0; --r) {
            if (wrd1[r] == wrd2[c])
                LCW[r][c] = 1 + LCW[r + 1][c + 1];
            else
                LCW[r][c] = 0;

            if (LCW[r][c] > maxLCW)
                maxLCW = LCW[r][c];
        }
        printLCW(LCW);
    }

    return maxLCW;
}

int
main()
{
    printf("\nLength of LCW : %d\n\n", LCW("secretary", "bisect"));
    printf("\nLength of LCW : %d\n\n", LCW("bisect", "secretary"));
}