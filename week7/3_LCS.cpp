// LONGEST COMMON SUB-SEQUENCE

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> intv;
typedef vector<intv> intvv;

void
printLCS(const intvv& LCS, const string& wrd1, const string& wrd2)
{
    printf("\n");

    int i, j, m, n;

    m = LCS.size();
    n = LCS[0].size();

    for (i = 0; i < n; ++i)
        if (i == 0)
            printf("  ");
        else
            printf("%c ", wrd2[i - 1]);
    printf("\n");

    for (i = 0; i < m; ++i) {
        if (i < m - 1)
            printf("%c ", wrd1[i]);
        else
            printf("  ");
        for (j = 0; j < n; ++j)
            printf("%d ", LCS[i][j]);
        printf("\n");
    }

    printf("\n");
}

string
LCS(const string wrd1, const string wrd2)
{
    int r, c, m, n, maxLCW;
    string lcs;

    m = wrd1.length(); // m rows
    n = wrd2.length(); // n columns

    intv row(n + 1, 0);
    intvv LCS(m + 1, row);
    row.clear();

    for (c = n - 1; c >= 0; --c) {
        for (r = m - 1; r >= 0; --r) {
            if (wrd1[r] == wrd2[c])
                LCS[r][c] = 1 + LCS[r + 1][c + 1];
            else
                LCS[r][c] = max(LCS[r + 1][c], LCS[r][c + 1]);
        }
    }

    printLCS(LCS, wrd1, wrd2);

    int maxNbr;
    r = c = 0;
    while (LCS[r][c] != 0) {
        maxNbr = max(LCS[r + 1][c + 1], LCS[r][c + 1]);
        maxNbr = max(maxNbr, LCS[r + 1][c]);

        if (LCS[r][c] == maxNbr + 1) {
            lcs += wrd1[r];
            r = r + 1;
            c = c + 1;
        } else if (LCS[r + 1][c] == maxNbr)
            r = r + 1;
        else
            c = c + 1;
    }

    return lcs;
}

int
main()
{
    printf("\nLCW : %s\n\n", LCS("secretary", "bisect").c_str());
    printf("\nLCW : %s\n\n", LCS("bisect", "secretary").c_str());
    printf("\nLCW : %s\n\n", LCS("putin", "lamput").c_str());
    printf("\nLCW : %s\n\n", LCS("donkey", "haput").c_str());
    printf("\nLCW : %s\n\n", LCS("lamput", "haput").c_str());
    printf("\nLCW : %s\n\n", LCS("grotesque", "protest").c_str());
}