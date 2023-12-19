#include "lib.h"

int main(){

    bigint a,b;

    a.size = 4;
    b.size = 4;

    a.value = (unsigned int*)malloc(a.size * sizeof(unsigned int));
    b.value = (unsigned int*)malloc(b.size * sizeof(unsigned int));
    
    a.value[0] = 99;
    a.value[1] = 99;
    a.value[2] = 99;
    a.value[3] = 99;
    b.value[0] = 99;
    b.value[1] = 99;
    b.value[2] = 99;
    b.value[3] = 99;
    // a.value[3] = 444444444;
    // b.value[0] = 111111111;
    // b.value[1] = 222222222;
    // b.value[2] = 333333333;
    // b.value[3] = 444444444;
    // a.value[4] = 66666666;
    // b.value[4] = 66666666;
    bigint c = add(a, b);
    // for(int i = c.size; i > 0; i--)
    //     printf("%d",c.value[i]);

    free(a.value);
    free(b.value);
    free(c.value);
    }