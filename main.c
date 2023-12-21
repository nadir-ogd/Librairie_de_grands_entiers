#include "lib.h"

int main(){
    bigint a,b;

    initBigint(&a, "111111111111111111111111111111111111");
    initBigint(&b, "88888888888888888888888888888888888");
    
    printf("a.size = %d\n",a.size);
    printf("b.size = %d\n",b.size);

    for(int i = a.size-1; i >= 0; i--)
        printf("a.value[%d] = %d\n",i,a.value[i]);

    for(int i = b.size-1; i >= 0; i--)
        printf("b.value[%d] = %d\n",i,b.value[i]);

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

    // printf("\n");

    // bigint s = product(a, b);
    // printf("\n< PRODUCT >\n");
    // printf("a * b = ");
    // for(int i = s.size-1; i >= 0; i--)
    //     printf("%d",s.value[i]);

    // printf("\n");

    // free(a.value);
    // free(b.value);
    // free(c.value);
    // free(d.value);
    // free(s.value);

    }