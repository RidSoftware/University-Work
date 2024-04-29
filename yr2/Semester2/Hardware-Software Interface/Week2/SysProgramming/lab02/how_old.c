#include <stdio.h>

int main(int argc, char *argv[])
{
    int current_year = 2022;
    int birth_year;
    int had_birthday = 0;           /* used as boolean */

    /* TODO: ask what year the user was born in */
	printf("what year were you born?");
	scanf("%d", &birth_year);
    /* TODO: ask whether the user has had their birthday yet this year */
	printf("have you had your birthday yet?");
	scanf("%d", &had_birthday);
    /* TODO: compute and display the user's age */
    int age = current_year - birth_year + had_birthday;
	printf("you are %d", age);
    return 0;
}
