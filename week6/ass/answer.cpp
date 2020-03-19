#include <algorithm>
#include <cstdio>
#include <vector>
#include <math.h>
using namespace std;

typedef vector<__int32_t> int32v;

inline __int64_t
vecsum(const int32v& v, __int32_t m, __int32_t n)
{
    __int64_t sum = 0;
    while (m < n)
        sum += v.at(m++);
    return sum;
}

__int64_t
max_sum(const int32v& b, __int32_t M, __int32_t K)
{
    __int32_t ps; // partition size
    if (K)
        ps = (__int32_t)ceil(M * 1.0 / K);
    else
        ps = 1;

    __int64_t sum, maxsum = 0;
    __int32_t m = M, j = 0, beg = 1;

    while (m >= ps) {
        sum = vecsum(b, beg + ps * j, beg + ps * (j + 1));
        if (sum > maxsum)
            maxsum = sum;
        m = m - ps;
        j = j + 1;
    }

    sum = vecsum(b, beg + ps * j, M + 1);
    if (sum > maxsum)
        maxsum = sum;

    return maxsum;
}

inline bool
alc(__int32_t K, __int32_t M, const int32v& b, __int64_t T)
{
    __int64_t sum = 0;

    for (__int32_t i = 1; i <= M && K > 0; ++i)
        if ((sum += b.at(i)) > T) {
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
print_alc(__int32_t K, __int32_t M, const int32v& b, __int64_t limit)
{
    __int64_t sum = 0;
    __int32_t i;
    int32v marked(M + 1, 0);

    for (i = M; i >= 1; --i)
        if ((sum += b.at(i)) > limit) {
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
        printf("%d", b.at(i));
        first = false;
    }

    printf("\n");
}

int
main()
{
    // initialization & input

    __int32_t M, K;
    scanf("%d %d", &M, &K);

    int32v b(M + 1, 0);
    for (__int32_t j = 1; j <= M; ++j)
        scanf("%d", &b[j]);

    // lower bound
    // __int64_t lower = *max_element(b.begin() + 1, b.end());

    __int64_t lower = 0;
    for (int i = 1; i <= M; ++i) {
        if (b[i] > lower) lower = b[i];
    }

    // upper bound
    __int64_t upper = max_sum(b, M, K);

    // optimum target T

    __int64_t T, opT, prevlower;
    while (lower <= upper) {

        do {
            T = (lower + upper) / 2;
            prevlower = lower;
            lower = T + 1;
        } while (!alc(K, M, b, T));

        opT = T;
        lower = prevlower;
        upper = T - 1;
    }

    print_alc(K, M, b, opT);

    return EXIT_SUCCESS;
}
