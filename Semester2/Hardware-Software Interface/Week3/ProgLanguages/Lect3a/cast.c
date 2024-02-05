#include <stdio.h>
#include <string.h>

struct chars {
    char a;
    char b;
    char c;
    char d;
};

int main(int argc, char *argv[])
{
    int x = 0x01234567;

    char *c1 = (char *) &x;
    printf("%x\n", *c1);
    printf("%x %x %x %x\n", c1[0], c1[1], c1[2], c1[3]);

    /* This will probably work, but it's undefined behaviour in standard C,
       because it violates the aliasing rules -- only char * is allowed to
       alias other types. */
    struct chars *c2 = (struct chars *) &x;
    printf("%x %x %x %x\n", c2->a, c2->b, c2->c, c2->d);

    /* This is legal. */
    struct chars c3;
    memcpy(&c3, &x, sizeof x);
    printf("%x %x %x %x\n", c3.a, c3.b, c3.c, c3.d);

    return 0;
}
