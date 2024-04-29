#include <stdio.h>

int scomp(const char *s0, const char *s1)
{
    int i = 0;
    while (s0[i] == s1[i]) {
        if (s0[i] == '\0')
            return 0;
        i++;
    }
    if (s0[i] == '\0' || s0[i] < s1[i])
        return -1;
    return 1;
}

int main(int argc, char *argv[])
{
    printf("banana banana %d\n", scomp("banana", "banana"));
    printf("banana banish %d\n", scomp("banana", "banish"));
    printf("ban band %d\n", scomp("ban", "band"));
    printf("banquet banana %d\n", scomp("banquet", "banana"));
    printf("bank ban %d\n", scomp("bank", "ban"));
    return 0;
}
