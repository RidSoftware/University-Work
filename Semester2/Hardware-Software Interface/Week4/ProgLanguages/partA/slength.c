#include <stdio.h>

int slength(const char *s)
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

int main(int argc, char *argv[])
{
    const char *q = "how long is this string?";
    printf("%s: %d characters\n", q, slength(q));
    return 0;
}
