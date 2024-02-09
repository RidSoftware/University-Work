#include <stdio.h>

int sq(int x)
{
    return x * x;
}

int main(int argc, char *argv[])
{
    int (*f)(int);

    printf("sq: %ld, &sq: %ld\n", (long) sq, (long) &sq);

    f = sq;
    printf("%d\n", f(3));

    return 0;
}
