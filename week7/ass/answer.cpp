#include <bits/stdc++.h>
using namespace std;

struct coords { long r, c; };

long
dist(coords& a, coords& b)
{
    return abs(b.r - a.r) + abs(b.c - a.c);
}

bool
operator<(const coords& a, const coords& b)
{
    return a.r < b.r;
}

int
main()
{
    long R, C, K, D, r, c, k;
    scanf("%ld %ld %ld %ld", &R, &C, &K, &D);

    vector<coords> dragon = { { 0, 0 } };

    for (k = 1; k <= D; ++k) {
        scanf("%ld %ld", &r, &c);
        dragon.push_back({ r, c });
    }

    // sort dragons by row value
    stable_sort(dragon.begin() + 1, dragon.end());

    long res, inf = R + C + 1;
    long minDist[D + 1][K + 1];

    for (r = 0; r < D+1; ++r)
        for (c = 0; c < K+1; ++c)
            minDist[r][c] = 0;

    for (c = 1; c <= K; ++c)
        for (r = c; r <= D - K + c; ++r)
            if (c == 1)
                minDist[r][c] = dist(dragon[0 /* start (0,0) */], dragon[r]);
            else {
        minDist[r][c] = inf;
        for (long k = c - 1; k < r; ++k)
            if ((res = minDist[k][c - 1] + dist(dragon[k], dragon[r])) <
                minDist[r][c])
                minDist[r][c] = res;
            }
/*
    printf("\n\n");
    for (r = 1; r <= D; ++r) {
        for (c = 1; c <= K; ++c)
            printf("%3ld ", minDist[r][c]);
        printf("\n");
    }
    printf("\n\n");
*/
    res = minDist[K][K];
    for (k = K+1; k <= D; ++k)
        if (minDist[k][K] < res)
            res = minDist[k][K];

    printf("%ld\n", res);
}