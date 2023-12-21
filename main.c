#include "lib.h"

int main(){

    init()

    
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
    free(c.value);
    free(d.value);
    free(s.value);

    }