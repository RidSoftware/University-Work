#include <stdio.h>

/* call by reference */
void doubler(int *x)
{
    *x *= 2;
}

int main(int argc, char *argv[])
{
    int y;
    y = 1;
    doubler(&y);                /* call by reference, sets y to 2 */
    printf("%d\n", y);          /* prints 2 */
    return 0;
}
