#include <stdio.h>

/* call by value */
void doubler(int x)
{
    x *= 2;
}

int main(int argc, char *argv[])
{
    int y;
    y = 1;
    doubler(y);                 /* call by value, no effect on y */
    printf("%d\n", y);          /* prints 1 */
    return 0;
}
