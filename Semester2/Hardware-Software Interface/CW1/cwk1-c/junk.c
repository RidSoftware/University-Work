#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct example {
    char * name;
    float height;
    int age;
};


struct cmd_input()

//main takes argc (number of cmd args), argv (array of cmd args)
int main(int argc, char *argv[]) {

    /* Check command-line arguments */
    if (argc !=2) {
        fprintf(stderr, "Usage: junk ARGUMENT\n");
        return 1;
    }
    


}