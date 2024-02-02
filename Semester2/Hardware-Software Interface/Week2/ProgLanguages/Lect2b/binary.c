#include <stdio.h>

int getBinary(FILE * fin, int *ch)
{
    int val;
    val = 0;
    while (*ch == '0' || *ch == '1') {
        val = 2 * val + (*ch) - '0';
        *ch = getc(fin);
    }
    return val;
}

int main(int argc, char *argv[])
{
    FILE *fin;
    int ch;
    int val;

    if (argc != 2) {
        printf("getBinary: wrong number of arguments\n");
        return 1;
    }
    if ((fin = fopen(argv[1], "r")) == NULL) {
        printf("getBinary: can't open %s\n", argv[1]);
        return 1;
    }
    ch = getc(fin);
    while (1) {
        while (ch != '0' && ch != '1' && ch != EOF)
            ch = getc(fin);
        if (ch == EOF)
            break;
        val = getBinary(fin, &ch);
        printf("%d\n", val);
    }
    fclose(fin);

    return 0;
}
