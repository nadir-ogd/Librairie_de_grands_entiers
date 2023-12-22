#include "lib.h"

int main(){
    bigint a,b;

    initBigint(&a, "1288888822222");
    initBigint(&b, "2222");
    
    printbigint(a);
    printbigint(b);

    printf("cmp(a, b) = %d\n",cmp(a, b));

    bigint c = add(a, b);
    printf("\n< ADDITION >\n");
    printf("a + b = ");
    printbigint(c);

    bigint d = sub(a, b);
    printf("\n< SUBSTRACTION >\n");
    printf("a - b = ");
    printbigint(d);

    bigint s = product(a, b);
    printf("\n< PRODUCT >\n");
    printf("a * b = ");
    printbigint(s);


    bigint *t = strtobigint("123");
    printbigint(*t);

    free(t);
    // free(a.value);
    // free(b.value);
    // free(c.value);
    // free(d.value);
    // free(s.value);

    }