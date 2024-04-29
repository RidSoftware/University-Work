#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned int n;

    printf("enter value> ");
    scanf("%u", &n);

    for (int i = 0; i < 32; i++)
        printf("%3d", i);
    putchar('\n');

    for (int i = 0; i < 32; i++) {
        printf("%3u", n & 1);
        n = n >> 1;
    }
    putchar('\n');

    return 0;
}
