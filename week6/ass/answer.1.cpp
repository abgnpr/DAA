#include <cstdio>
#include <math.h>
using namespace std;

// optimized using array

inline int
Sum(const int* v, int m, int n)
{
    int sum = 0;
    while (m < n)
        sum += v[m++];
    return sum;
}

int
max_sum(const int* b, int M, int K)
{
    int ps; // partition size
    if (K)
        ps = (int)ceil(M * 1.0 / K);
    else
        ps = 1;

    int sum, maxsum = 0;
    int m = M, j = 0, beg = 1;

    while (m >= ps) {
        sum = Sum(b, beg + ps * j, beg + ps * (j + 1));
        if (sum > maxsum)
            maxsum = sum;
        m = m - ps;
        j = j + 1;
    }

    sum = Sum(b, beg + ps * j, M + 1);
    if (sum > maxsum)
        maxsum = sum;

    return maxsum;
}

inline bool
alc(int K, int M, const int* b, int T)
{
    int sum = 0;

    for (int i = 1; i <= M && K > 0; ++i)
        if ((sum += b[i]) > T) {
            sum = 0;
            --i;
            --K;
        }

    if (K < 1)
        return false;
    else
        return true;
}

void
print_alc(int K, int M, const int* b, int limit)
{
    int sum = 0;
    int i;
    int marked[M + 1];
    for (i = 1; i <= M; ++i)
        marked[i] = 0;

    for (i = M; i >= 1; --i)
        if ((sum += b[i]) > limit) {
            sum = 0;
            marked[i + 1] = 1;
            ++i;
            --K;
        }

    for (i = 2; i <= M && K > 1; ++i)
        if (!marked[i]) {
            marked[i] = 1;
            --K;
        }

    bool first = true;
    for (i = 1; i <= M; ++i) {
        if (marked[i])
            printf(" /");
        if (!first)
            printf(" ");
        printf("%d", b[i]);
        first = false;
    }

    printf("\n");
}

int
main()
{
    // initialization & input

    int M, K;
    scanf("%d %d", &M, &K);

    int b[M + 1];
    for (int j = 1; j <= M; ++j)
        scanf("%d", &b[j]);

    // lower bound
    int lower = 0;
    for (int i = 1; i <= M; ++i) {
        if (b[i] > lower)
            lower = b[i];
    }

    // upper bound
    int upper = max_sum(b, M, K);

    // optimum target T

    int T, opT, prevlower;
    while (lower <= upper) {
        T = (lower + upper) / 2;
        if (alc(K, M, b, T)) {
            opT = T;
            upper = T - 1;
        } else {
            lower = T + 1;
        }
    }

    print_alc(K, M, b, opT);

    return EXIT_SUCCESS;
}
