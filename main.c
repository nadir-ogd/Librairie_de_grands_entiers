#include "lib.h"

int main(){

    bigint a,b;

    b.size = 3;
    a.size = 2;

    a.value = (unsigned int*)malloc(a.size * sizeof(unsigned int));
    b.value = (unsigned int*)malloc(b.size * sizeof(unsigned int));
    
    a.value[0] = 1;
    a.value[1] = 2;
    b.value[0] = 1;
    b.value[1] = 1;
    b.value[2] = 12;

    
    printf("cmp(a, b) = %d\n",cmp(a, b));

    // bigint c = product(a, b);
    // printf("\n< PRODUCT >\n");
    // printf("a * b = ");
    // for(int i = c.size-1; i >= 0; i--)
    //     printf("%d",c.value[i]);

    // printf("\n");

    free(a.value);
    free(b.value);
    // free(c.value);

    }