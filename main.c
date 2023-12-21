#include "lib.h"

int main(){

    bigint a,b;

    a.size = 3;
    b.size = 2;

    a.value = (unsigned int*)malloc(a.size * sizeof(unsigned int));
    b.value = (unsigned int*)malloc(b.size * sizeof(unsigned int));
    
    b.value[0] = 1;
    b.value[1] = 2;
    a.value[0] = 1;
    a.value[1] = 1;
    a.value[2] = 215;

    
    printf("cmp(a, b) = %d\n",cmp(a, b));

    bigint c = add(a, b);
    printf("\n< ADDITION >\n");
    printf("a + b = ");
    for(int i = c.size-1; i >= 0; i--)
        printf("%d",c.value[i]);

    printf("\n");

    bigint d = sub(a, b);
    printf("\n< SUBSTRACTION >\n");
    printf("a - b = ");
    for(int i = d.size-1; i >= 0; i--)
        printf("%d",d.value[i]);

    printf("\n");

    bigint s = product(a, b);
    printf("\n< PRODUCT >\n");
    printf("a * b = ");
    for(int i = s.size-1; i >= 0; i--)
        printf("%d",s.value[i]);

    printf("\n");

    free(a.value);
    free(b.value);
    // free(c.value);

    }