#include <stdio.h>

void swap(int a, int b)
{
    int t;
    t = a;
    a = b;
    b = t;
}

int main(int argc, char *argv[])
{
    int x, y;
    x = 1;
    y = 2;
    swap(x, y);
    printf("x: %d, y: %d\n", x, y);
    return 0;
}
