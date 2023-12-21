#include "./lib.h"

//External functions
unsigned int countDigits(unsigned int x) {
    unsigned int count = 0;
    while (x > 0) {
        x /= 10;
        count++;
    }
    return count;
}

unsigned int power(unsigned int base, unsigned int exponent) {
    unsigned int result = 1;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }
    return result;
}

void initBigint(bigint *nb, const char *str) {
    int len = strlen(str);
    nb->size = (len + 8) / 9;//+8 : car la plus petite valeur pour len est 1
    nb->value = (unsigned int *)malloc(nb->size * sizeof(unsigned int));
    if (nb->value == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < nb->size; ++i) {
        nb->value[i] = 0;
    }

    int ind = 0;
    for (int i = len - 1; i >= 0; i -= 9) {
        int tmp = 0;
        for (int j = i - 8; j <= i; ++j) {
            if (j >= 0) {
                tmp = tmp * 10 + (str[j] - '0');
            }
        }
        nb->value[ind++] = tmp;
    }
}

int cmp(bigint a, bigint b){

    if (a.size > b.size){//a > b 
        for(unsigned int i = 0; i < b.size; i++)
            if (a.value[i] != b.value[i])
                return i;
            return b.size;
    }
    else if (a.size < b.size) {//b > a
        for(unsigned int i = 0; i < a.size; i++)
            if (a.value[i] != b.value[i])
                return -i;
            return -(a.size);
    }
    else{//a > b ou b < a
        for(unsigned int i = 0; i < a.size; i++){
            if (a.value[i] > b.value[i])
                return i;
            if (a.value[i] < b.value[i])
                return -i;
        }
    }

    return 0; 
}

bigint add(bigint a, bigint b) {
    bigint c;
    unsigned int carry = 0, nb_digit_a, nb_digit_b, max_nb_digits;

    c.size = (a.size >= b.size) ? a.size : b.size;

    c.value = (unsigned int *)malloc(c.size * sizeof(unsigned int));

    for (unsigned int i = 0; i < c.size; i++) {
        nb_digit_a = (i < a.size) ? countDigits(a.value[i]) : 0;
        nb_digit_b = (i < b.size) ? countDigits(b.value[i]) : 0;

        max_nb_digits = (nb_digit_a > nb_digit_b) ? nb_digit_a : nb_digit_b;

        unsigned int sum = 0;
        if (i < a.size) {
            sum += a.value[i];
        }
        if (i < b.size) {
            sum += b.value[i];
        }

        sum += carry;
    
        if (countDigits(sum) > max_nb_digits && i != c.size - 1) {
            carry = 1;
            c.value[i] = sum % power(10, max_nb_digits);
        } else {
            carry = 0;
            c.value[i] = sum;
        }
    }


        // cas où le dernier élément de tableau a une retenue et s'écrit pas dans 10^9
        if (countDigits(c.value[c.size-1]) > 9) {
            c.size++;
            c.value = realloc(c.value, c.size * sizeof(unsigned int));

            c.value[c.size - 1] = c.value[c.size - 2] / power(10, max_nb_digits);;
            
            c.value[c.size - 2] = c.value[c.size - 2] % power(10, max_nb_digits);
        }
    return c;
}

bigint sub(bigint a, bigint b){
    bigint c;
    unsigned int borrow = 0, nb_digit_a, nb_digit_b, max_nb_digits;

    if (cmp(a, b) < 0) {
        fprintf(stderr, "Erreur : a doit être supérieur ou égal à b pour la soustraction.\n");
        exit(EXIT_FAILURE);
    }

    c.size = a.size;
    c.value = (unsigned int *)malloc(c.size * sizeof(unsigned int));

    for (unsigned int i = 0; i < c.size; i++) {
        nb_digit_a = (i < a.size) ? countDigits(a.value[i]) : 0;
        nb_digit_b = (i < b.size) ? countDigits(b.value[i]) : 0;

        max_nb_digits = (nb_digit_a > nb_digit_b) ? nb_digit_a : nb_digit_b;

        int diff = 0;
        if (i < b.size) {
            diff = a.value[i] - b.value[i] - borrow;
        } else {
            diff = a.value[i] - borrow;
        }

        if (diff < 0) {
            borrow = 1;
            diff += power(10, max_nb_digits);
        } else
            borrow = 0;

        c.value[i] = diff;
    }

    while (c.size > 1 && c.value[c.size - 1] == 0) {
        c.size--;
        c.value = realloc(c.value, c.size * sizeof(unsigned int));
    }

    return c;
}

// bigint product(bigint a, bigint b){
//     bigint c;
//     c.size = a.size;
//     c.value = (unsigned int *)malloc(c.size * sizeof(unsigned int));
    
//     bigint one;
//     one.size = 1;
//     one.value = (unsigned int *)malloc(one.size * sizeof(unsigned int));
//     one.value[0] = 1;
    
//     bigint zero;
//     zero.size = 1;
//     zero.value = (unsigned int *)malloc(zero.size * sizeof(unsigned int));
//     one.value[0] = 0;

//     bigint tmp;
//     tmp.size = b.size;
//     tmp.value = (unsigned int *)malloc(tmp.size * sizeof(unsigned int));

//     for (unsigned int i = 0; i < tmp.size; i++)
//         tmp.value[i] = b.value[i];

//     printf("Avant c : ");
//     for(int i = c.size-1; i >= 0; i--)
//         printf("%d",c.value[i]);

//     printf("\nAvant tmp : ");
//     for(int i = tmp.size-1; i >= 0; i--)
//         printf("%d",tmp.value[i]);

//     c = add(zero, zero);
//     if (cmp(a, b) > 0){
//         while(cmp(tmp, zero) != 0){
//             c = add(c, a);
//             tmp = sub(tmp, one);

//             printf("\nDans boucle c = ");
//             for(int i = c.size-1; i >= 0; i--)
//                 printf("%d",c.value[i]);

//             printf("\nDans boucle tmp = ");
//             for(int i = tmp.size-1; i >= 0; i--)
//                 printf("%d",tmp.value[i]);

//             printf("\n cmp(tmp, zero) = %d\n", cmp(tmp, zero));
//         }
//     }

//     printf("\nAprès c = ");
//     for(int i = c.size-1; i >= 0; i--)
//         printf("%d",c.value[i]);
    
//     printf("\nAprès tmp = ");
//     for(int i = tmp.size-1; i >= 0; i--)
//         printf("%d",tmp.value[i]);
//     return c;
// }

bigint product(bigint a, bigint b) {
    bigint one;
    one.size = 1;
    one.value = (unsigned int *)calloc(one.size, sizeof(unsigned int));
    one.value[0] = 1;

    bigint zero;
    zero.size = b.size;
    zero.value = (unsigned int *)calloc(zero.size, sizeof(unsigned int));
    zero.value[0] = 0;

    bigint tmp;
    tmp.size = b.size;
    tmp.value = (unsigned int *)calloc(tmp.size, sizeof(unsigned int));
         
    bigint c;
    c.size = a.size + b.size;
    c = add(zero, zero);

    // printf("\nc avant = ");
    for(int i = c.size-1; i >= 0; i--)
        printf("%d",c.value[i]);

    // printf("\nb avant = ");
    for(int i = b.size-1; i >= 0; i--)
        printf("%d",b.value[i]);

    // printf("\ntmp avant = ");
    for(int i = tmp.size-1; i >= 0; i--)
        printf("%d",tmp.value[i]);

    // printf("\ncmp(tmp, zero) = %d\n",cmp(tmp, zero));
    while (cmp(b, tmp) == 0) {
        c = add(c, a);
        tmp = sub(tmp, one);

        // printf("\nc après = ");
        for(int i = c.size-1; i >= 0; i--)
            printf("%d",c.value[i]);
        
        // printf("\ntmp après = ");
        for(int i = tmp.size-1; i >= 0; i--)
            printf("%d",tmp.value[i]);

        // printf("\none après = ");
        for(int i = one.size-1; i >= 0; i--)
            printf("%d",one.value[i]);
            
    }

    free(one.value);
    free(zero.value);
    free(tmp.value);

    return c;
}




// bigint product(bigint a, bigint b) {
//     bigint c;
//     c.size = a.size + b.size;
//     c.value = (unsigned int *)calloc(c.size, sizeof(unsigned int));

//     for (unsigned int i = 0; i < a.size; i++) {
//         unsigned int carry = 0;
//         for (unsigned int j = 0; j < b.size; j++) {
//             unsigned long long p = (unsigned long long)a.value[i] * b.value[j] + c.value[i + j] + carry;
//             c.value[i + j] = p % power(10, 9);
//             carry = p / power(10, 9);
//             printf("p = %u | c.value[%d + %d] = %d | carry = %d\n",p,i,j,c.value[i+j],carry);
//         }
//         c.value[i + b.size] += carry;
//     }
    
//     // Retirer les zéros non significatifs à gauche
//     while (c.size > 1 && c.value[c.size - 1] == 0) {
//         c.size--;
//         c.value = realloc(c.value, c.size * sizeof(unsigned int));
//     }

//     return c;
// }


void intdiv(bigint a, bigint b, bigint *quotient, bigint *modulo){

}

bigint pow2n(unsigned int n){

} 

void printbigint(bigint n){

}

char *biginttostr(bigint n){

}

bigint *strtobigint(char *s){

}

char *biginttosubstr(bigint n, int first, int last){

}