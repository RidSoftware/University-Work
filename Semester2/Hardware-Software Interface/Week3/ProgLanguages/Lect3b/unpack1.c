#include <stdio.h>

#define BYTE0 0x000000ff

int main(int argc, char *argv[])
{
    int word = 0x61626364;

    for (int i = 0; i < 4; i++) {
        printf("%8x\n", word & BYTE0);
        word = word >> 8;
    }

    return 0;
}
