#include <cstdio>

long
fib(long n)
{
    long fibtable[n + 1];

    fibtable[0] = 0;
    fibtable[1] = 1;

    for (long i = 2; i <= n; ++i)
        fibtable[i] = fibtable[i - 1] + fibtable[i - 2];

    return fibtable[n];
}

int
main()
{
    long f;

    f = fib(0);
    printf("\n%ld\n", f);

    f = fib(10);
    printf("\n%ld\n", f);

    f = fib(199);
    printf("\n%ld\n\n", f);

}