#include <stdio.h>

void copy(FILE * fin, FILE * fout)
{
    int ch;
    ch = getc(fin);
    while (ch != EOF) {
        putc(ch, fout);
        ch = getc(fin);
    }
}

int main(int argc, char *argv[])
{
    FILE *fin, *fout;

    if (argc != 3) {
        printf("copy: wrong number of arguments\n");
        return 1;
    }
    fin = fopen(argv[1], "r");
    if (fin == NULL) {
        printf("copy: can't open %s\n", argv[1]);
        return 1;
    }
    fout = fopen(argv[2], "w");
    if (fout == NULL) {
        printf("copy: can't open %s\n", argv[2]);
        fclose(fin);
        return 1;
    }
    copy(fin, fout);
    fclose(fin);
    fclose(fout);

    return 0;
}
