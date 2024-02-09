#include <stdio.h>
#include <stdlib.h>

#define MAX 256

struct freq {
    int ch;
    int count;
};

struct freq f[MAX];
int fp;

void incFreq(int ch)
{
    for (int i = 0; i < fp; i++) {
        if (f[i].ch == ch) {
            f[i].count++;
            return;
        }
    }
    if (fp == MAX) {
        printf("more than %d different characters\n", MAX);
        exit(1);
    }
    f[fp].ch = ch;
    f[fp].count = 1;
    fp++;
}

void showFreq(void)
{
    for (int i = 0; i < fp; i++) {
        printf("%c : %d\n", f[i].ch, f[i].count);
    }
}

int main(int argc, char *argv[])
{
    FILE *fin;
    if ((fin = fopen(argv[1], "r")) == NULL) {
        printf("can't open %s\n", argv[1]);
        return 1;
    }
    fp = 0;
    while (1) {
        int ch = getc(fin);
        if (ch == EOF)
            break;
        incFreq(ch);
    }
    fclose(fin);
    showFreq();
    return 0;
}
