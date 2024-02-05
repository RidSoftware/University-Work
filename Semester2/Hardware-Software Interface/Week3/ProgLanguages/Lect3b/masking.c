#include <stdio.h>

#define BYTE0 0x000000ff
#define BYTE1 0x0000ff00
#define BYTE2 0x00ff0000
#define BYTE3 0xff000000

int main(int argc, char *argv[])
{
    /* 00000064
       00006300
       00620000
       61000000
     */
    int word = 0x61626364;
    printf("%8x\n", word & BYTE0);
    printf("%8x\n", word & BYTE1);
    printf("%8x\n", word & BYTE2);
    printf("%8x\n", word & BYTE3);
    return 0;
}
