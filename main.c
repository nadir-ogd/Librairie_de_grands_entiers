#include "lib_big_int.h"

int main(){
    
    unsigned int n = 10;
    int result = Mersenne(n);
    
    if (result) 
        printf("2^%u - 1 est un nombre premier de Mersenne.\n", n);
    else
        printf("2^%u - 1 n'est pas un nombre premier de Mersenne.\n", n);
    

    // printf("a = ");
    // printbigint(*a);

    // printf("\nb = ");
    // printbigint(b);
    // // bigint s = product(a, b);
    // // printbigint(s);

    // bigint q, m;
    // intdiv(b, a, &q, &m);

    // printf("\nQuotien : ");
    // printbigint(q);
    // printf("\nModulo : ");
    // printbigint(m);*
    }