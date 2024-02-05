#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned int n;

    printf("enter number> ");
    scanf("%u", &n);

    for (int i = 31; i > 0; i--)
        printf("%3d", i);
    putchar('\n');

    for (int i = 0; i < 31; i++) {
        printf("%3u", n >> 31);
        n = n << 1;
    }
    putchar('\n');

    return 0;
}
