#include <stdio.h>

#define MAX 5

int inc(int x)
{
    return x + 1;
}

int twice(int x)
{
    return 2 * x;
}

void map(int (*f)(int), int a[], int n)
{
    for (int i = 0; i < n; i++)
        a[i] = f(a[i]);
}

void show(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    int a[MAX];
    for (int i = 0; i < MAX; i++)
        a[i] = i;
    show(a, 5);
    map(inc, a, 5);
    show(a, 5);
    map(twice, a, 5);
    show(a, 5);
    return 0;
}
