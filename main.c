#include "lib.h"

int main(){
    bigint a,b;

    initBigint(&a, "1000000022222");
    initBigint(&b, "2222000001000");
    

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


    bigint *t = strtobigint("120000001000003");
    printbigint(*t);

    char *w = biginttostr(a);
    printf("str = %s\n",w);

    // free(t);
    free(a.value);
    //free(b.value);
    // free(c.value);
    // free(d.value);
    // free(s.value);

    }