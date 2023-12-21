#include "lib.h"

int main(){
    bigint a,b;

    initBigint(&a, "323456789123456789123456789123456789");
    initBigint(&b, "223456789123456789123456789123456789");
    
    printf("a.size = %d\n",a.size);
    printf("b.size = %d\n",b.size);
    printf("cmp(a, b) = %d\n",cmp(a, b));

    // bigint c = add(a, b);
    // printf("\n< ADDITION >\n");
    // printf("a + b = ");
    // for(int i = c.size-1; i >= 0; i--)
    //     printf("%d",c.value[i]);

    // printf("\n");

    // bigint d = sub(a, b);
    // printf("\n< SUBSTRACTION >\n");
    // printf("a - b = ");
    // for(int i = d.size-1; i >= 0; i--)
    //     printf("%d",d.value[i]);

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