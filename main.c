#include "lib.h"

int main(){

    bigint a,b;

    a.size = 5;
    b.size = 5;

    a.value = (unsigned int*)malloc(a.size * sizeof(unsigned int));
    b.value = (unsigned int*)malloc(b.size * sizeof(unsigned int));
    
    a.value[0] = 111111111;
    a.value[1] = 222222222;
    a.value[2] = 333333333;
    a.value[3] = 444444444;
    b.value[0] = 111111111;
    b.value[1] = 222222222;
    b.value[2] = 333333333;
    b.value[3] = 444444444;
    a.value[4] = 66666666;
    b.value[4] = 66666666;

    printf("cmp(a ; b) = %d\n",cmp(a,b));

    free(a.value);
    free(b.value);
    }