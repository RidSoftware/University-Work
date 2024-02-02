#include <stdio.h>

int poly(int a, int b, int c, int x)
{
    return a * x * x + b * x + c;
}

int main(int argc, char *argv[])
{
    printf("%d\n", poly(2, 4, 3, 5));
    return 0;
}
