#include <stdio.h>
#include <stdlib.h>

int slength(const char *s)
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

char *scopy(const char *s)
{
    int l = slength(s) + 1;
    char *c = malloc(l);
    for (int i = 0; i < l; i++) {
        c[i] = s[i];
    }
    return c;
}

int main(int argc, char *argv[])
{
    char *s = scopy("water: the drink that is wet!");
    printf("%s\n", s);
    free(s);
    return 0;
}
