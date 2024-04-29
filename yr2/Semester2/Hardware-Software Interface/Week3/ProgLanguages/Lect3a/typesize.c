#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("char:   %zd\n", sizeof(char));
    printf("short:  %zd\n", sizeof(short));
    printf("int:    %zd\n", sizeof(int));
    printf("long:   %zd\n", sizeof(long));
    printf("float:  %zd\n", sizeof(float));
    printf("double: %zd\n", sizeof(double));
    printf("char *: %zd\n", sizeof(char *));
    return 0;
}
