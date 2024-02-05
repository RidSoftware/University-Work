#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;

    /* TODO: read integer as an int into i */
	scanf("%d", &i);
	
	
    int smallest = i;
    int largest = i;

    /* TODO: loop forever until '0' is typed in */
    while (1) {
        if(i==0){break;}
        else {
        
        /* TODO: if new number is smaller than smallest, update smallest */
		if (largest < i) {largest = i;}
        /* TODO: if new number is larger than largest, update largest */
		if  (smallest > i) {smallest = i;}
        /* TODO: read the next number as an int into i */
        	scanf("%d", &i);
        }
    }

    printf("smallest: %d, largest: %d\n", smallest, largest);

    return 0;
}
