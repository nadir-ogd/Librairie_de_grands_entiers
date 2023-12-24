#include "lib.h"

int main(){
    bigint a,b;

    initBigint(&a, "10000012222222223333333");
    initBigint(&b, "10000011115555555599999");
    

    printbigint(a);
    printbigint(b);

    // printf("cmp(a, b) = %d\n",cmp(a, b));

    // bigint c = add(a, b);
    // printf("\n< ADDITION >\n");
    // printf("a + b = ");
    // printbigint(c);

    // // bigint d = sub(a, b);
    // // printf("\n< SUBSTRACTION >\n");
    // // printf("a - b = ");
    // // printbigint(d);

    // bigint s = product(a, b);
    // printf("\n< PRODUCT >\n");
    // printf("a * b = ");
    // printbigint(s);


    // bigint *t = strtobigint("120000001000003");
    // printbigint(*t);

    // bigint q, m;
    // intdiv(a, b, &q, &m);

    // printf("\nQuotien :");
    // printbigint(q);
    // printf("\nModulo : ");
    // printbigint(m);

    // int n = 6;
    // bigint p = pow2n(n);

    char *s0 = biginttostr(a);
    printf("a en string = %s\n",s0);

    char *s = biginttosubstr(a, 0, 1);
    printf("a entre pos 1 et pos 2 = %s\n",s);

    char *s2 = biginttosubstr(a, 0, 2);
    printf("b entre pos 0 et pos 2 = %s\n",s2);
    // printf("size of p = %d\n",p.size);
    // printf("\n2 ** %d = ",n);
    // printbigint(p);
    // // free(t);
    // free(a.value);
    //free(b.value);
    // free(c.value);
    // free(d.value);
    // free(s.value);

    }