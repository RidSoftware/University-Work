#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    i = 50;
    printf("value inside variable: %d\n", i);

    int *ptr = &i;

    /* "(long)" here is a cast -- it's forcing the pointer value to be
       converted to the type "long", so we can print it out using the %lx
       format in printf. */

    printf("Address of pointer: %lx\n", (long) &ptr);
    printf("Address inside pointer: %lx\n\n", (long) ptr);
    printf("Address of variable: %lx\n", (long) ptr);
    /* use indirection to get integer value at this address */
    printf("Value inside variable: %d\n", *ptr);

    return 0;
}
