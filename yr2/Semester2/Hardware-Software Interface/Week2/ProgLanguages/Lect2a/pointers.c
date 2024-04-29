#include <stdio.h>
#include <stdlib.h>

/* automatic variables stored on the stack */
void printVariableInfo(void)
{
    char c1 = 'a';              /* a character */
    printf("bytes for storing a char:\t\t %ld\n", sizeof(c1));
    printf("char value=%c\n", c1);

    int i1 = 48;                /* an integer */
    printf("bytes for storing an int:\t\t %ld\n", sizeof(i1));
    printf("int value=%d\n", i1);

    float f1 = 3.14;            /* a float */
    printf("bytes for storing a float:\t\t %ld\n", sizeof(f1));
    printf("float value=%f\n", f1);
}






void printPointerInfo(void)
{
    /* characters */

    char *c2;                   /* create a character pointer to a random memory address */
    printf("bytes for storing a pointer to a char:\t %ld\n", sizeof(c2));

    char c = 'a';               /* create a local variable */
    c2 = &c;                    /* update pointer address to point to local variable's address */

    printf("address for char pointer: %lx\n", (long) c2);
    printf("value at char pointer address: %c\n\n", *c2);





    /* integers */

    int *i2;                    /* create an int pointer to a random memory address */
    printf("bytes for storing a pointer to an int:\t %ld\n", sizeof(i2));

    int i = 48;                 /* create a local variable */
    i2 = &i;                    /* update pointer address to point to local variable's address */

    printf("address for int pointer: %lx\n", (long) i2);
    printf("value at int pointer address: %d\n\n", *i2);



    /* floats */

    float *f2;                  /* create an int pointer to a random memory address */
    printf("bytes for storing a pointer to a float:\t %ld\n", sizeof(f2));

    float f = 3.14;             /* create a local variable */
    f2 = &f;                    /* update pointer address to point to local variable's address */

    printf("address for float pointer: %lx\n", (long) f2);
    printf("value at float pointer address: %f\n", *f2);
}



int main(int argc, char *argv[])
{
    /* printf("\n==== automatic variables info ====\n"); */
    /* printVariableInfo(); */

    printf("\n==== pointers info ===============\n");
    printPointerInfo();

    return 0;
}
