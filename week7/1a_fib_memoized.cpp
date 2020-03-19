#include <cstdio>
#include <map>

typedef std::map<long, long> memo;

long
fib(long n, memo& fibtable)
{
    if (fibtable.find(n) != fibtable.end())
        return fibtable.at(n);

    long value;

    if (n == 0 || n == 1)
        value = n;
    else
        value = fib(n - 1, fibtable) + fib(n - 2, fibtable);

    fibtable.insert({ n, value });
    return value;
}

int
main()
{
    memo fibtable;
    long f = fib(9999, fibtable);
    printf("\n\n%ld\n\n", f);
    return EXIT_SUCCESS;
}