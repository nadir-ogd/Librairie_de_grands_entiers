#include "lib.h"

int main(){

    bigint a,b;

    a.size = 3;
    b.size = 3;

    a.value = (unsigned int*)malloc(a.size * sizeof(unsigned int));
    b.value = (unsigned int*)malloc(b.size * sizeof(unsigned int));
    
    a.value[2] = 999999999;
    a.value[1] = 333333333;
    a.value[0] = 4444444;
    b.value[2] = 999999999;
    b.value[1] = 333333333;
    b.value[0] = 1111111;
    // b.value[4] = 9999999;
    // b.value[5] = 9999999; 
    // a.value[3] = 444444444;
    // b.value[0] = 111111111;
    // b.value[1] = 222222222;
    // b.value[2] = 333333333;
    // b.value[3] = 444444444;
    // a.value[4] = 66666666;
    // b.value[4] = 66666666;
    
    bigint c = add(a, b);

    printf("< ADD >\n c = ");
    printf("Taille de c = %d\n",c.size);

    for(int i = c.size-1; i >= 0; i--)
        printf("%d\n",c.value[i]);
        
    bigint d = sub(a, b);

    printf("\n< SUB >\n d = ");
    for(int i = d.size-1; i >= 0; i--)
        printf("%d",d.value[i]);

    printf("Taille de d = %d\n",d.size);

    free(a.value);
    free(b.value);
    free(c.value);
    free(d.value);
    }