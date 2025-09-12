#include <stdio.h>

/* count characters in input; 1st version */

int main(void) {
    int c;
    
    long nc;
    nc = 0;
    
    while ((c=getchar()) != EOF){ // ctrl + D
        ++nc;
    }
    
    printf("%ld\n", nc);

    return 0;
}