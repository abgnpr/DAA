// EDIT DISTANCE
//  also, Levenshtein Distance

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> intv;
typedef vector<intv> intvv;

struct edits
{
    edits()
      : ins(0)
      , dels(0)
      , subs(0)
    {}
    int ins, dels, subs;
};

void
print(const intvv& M, const string& wrd1, const string& wrd2)
{
    printf("\n");

    int i, j, m, n;

    m = M.size();
    n = M[0].size();

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
            printf("%d ", M[i][j]);
        printf("\n");
    }

    printf("\n");
}

edits
ED(string a, string b)
{
    int r, c, m, n;

    m = a.length(); // m rows
    n = b.length(); // n columns

    intv row(n + 1, 0);
    intvv ED(m + 1, row);

    for (r = 0; r < m + 1; ++r)
        ED[r][n] = m - r;

    for (c = 0; c < n + 1; ++c)
        ED[m][c] = n - c;

    for (c = n - 1; c >= 0; --c)
        for (r = m - 1; r >= 0; --r)
            if (a[r] == b[c])
                ED[r][c] = ED[r + 1][c + 1];
            else
                ED[r][c] =
                  1 + min({ ED[r + 1][c + 1], ED[r][c + 1], ED[r + 1][c] });

    print(ED, a, b);

    edits ed;
    r = c = 0;
    while (ED[r][c] != 0) {
        int Min = min({ ED[r + 1][c + 1], ED[r + 1][c], ED[r][c + 1] });
        if (Min == ED[r + 1][c]) {
            ed.dels += 1;
            r = r + 1;
        } else if (Min == ED[r][c + 1]) {
            ed.ins += 1;
            c = c + 1;
        } else {
            if (Min != 0 && Min + 1 == ED[r][c])
                ed.subs += 1;
            r = r + 1;
            c = c + 1;
        }
    }

    return ed;
}

int
main()
{
    edits ed;

    ed = ED("hello", "malloc");
    printf("+%d -%d\n", ed.ins+ed.subs, ed.dels+ed.subs);

    ed = ED("bisect", "secret");
    printf("+%d -%d\n", ed.ins+ed.subs, ed.dels+ed.subs);
}