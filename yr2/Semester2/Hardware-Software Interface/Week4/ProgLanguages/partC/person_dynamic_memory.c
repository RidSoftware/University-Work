#include <stdio.h>
#include <stdlib.h>

struct person {
    const char *name;
    int age;
    float height;
};

int main(int argc, char *argv[])
{
    struct person *chris = malloc(sizeof *chris);

    chris->name = "Chris";
    chris->height = 1.75;
    chris->age = 27;

    printf("Chris's name: %s\n", chris->name);
    printf("Chris's height: %.2f\n", chris->height);
    printf("Chris's age: %d\n", chris->age);

    free(chris);

    return 0;
}
