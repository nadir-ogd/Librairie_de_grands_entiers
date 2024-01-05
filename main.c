#include "lib_big_int.h"

int Mersenne(unsigned int n) {
    bigint *Mn, *S, *two, *one;
    Mn = strtobigint("0");
    ("4");//S(1) = 4
    S = strtobigint("2");
    one = ("1");

    // Calcul de M_n = 2^n - 1
    *Mn = sub(pow2n(n), *one);
    printf("M_n (2^n - 1) = ");
    printbigint(*Mn);

    // Test de Lucas-Lehmer
    for (unsigned int k = 2; k < n; k++) {
        bigint Sk = product(*S, *S);
        printf("Sk à l'itération %u = ",k);
        printbigint(Sk);
        printf("\n");
        *S = sub(Sk, *two);
    }

    printf("S(p-1) = ");
    printbigint(*S);

    // Vérification si le résultat final est nul
    bigint q,r;
    intdiv(*S, *Mn, &q, &r);
    printf("\nQuotien : ");
    printbigint(q);
    printf("\nModulo : ");
    printbigint(r);

    int result = (r.size == 1 && r.value[0] == 0);

    // Libération de la mémoire allouée
    freebigint(Mn);
    freebigint(S);
    freebigint(two);
    freebigint(one);

    return result;
}

int main(){
    
    unsigned int n = 9;
    int result = Mersenne(n);
    
    if (result) 
        printf("2^%u - 1 est un nombre premier de Mersenne.\n", n);
    else
        printf("2^%u - 1 n'est pas un nombre premier de Mersenne.\n", n);
    bigint a,b;
    initBigint(&a, "11111111111");
    b = pow2n(50);

    // // bigint s = product(a, b);
    // // printbigint(s);

    // bigint q, m;
    // intdiv(b, a, &q, &m);

    // printf("\nQuotien : ");
    // printbigint(q);
    // printf("\nModulo : ");
    // printbigint(m);*
    }