#include "./lib.h"

//external functions
unsigned int countDigits(unsigned int x) {
    if (x == 0) {
        return 1;
    }
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


void copyAndFormat(bigint original, unsigned int *result) {
    unsigned int ind = 0;

    // Copier et formater les chiffres
    for (unsigned int i = 0; i < original.size; i++) {
        unsigned int val = original.value[i];

        // Copier chaque chiffre individuel dans le tableau résultant
        while (val != 0) {
            result[ind++] = val % 10;
            val /= 10;
        }
    }
}

int cmp(bigint a, bigint b) {
    unsigned int a_bit_size = 0, b_bit_size = 0;

    for (unsigned int i = 0; i < a.size; i++)
        a_bit_size += countDigits(a.value[i]);
    for (unsigned int i = 0; i < b.size; i++)
        b_bit_size += countDigits(b.value[i]);

    unsigned int *a_copy = (unsigned int *)malloc(a_bit_size * sizeof(unsigned int));
    unsigned int *b_copy = (unsigned int *)malloc(b_bit_size * sizeof(unsigned int));

    // unsigned int ind = 0;
    // for (unsigned int i = 0; i < a.size; i++) {
    //     unsigned int val = a.value[i];
    //     while (val != 0) {
    //         a_copy[ind++] = val % 10;
    //         val /= 10;
    //     }
    // }

    // ind = 0;
    // for (unsigned int i = 0; i < b.size; i++) {
    //     unsigned int val = b.value[i];
    //     while (val != 0) {
    //         b_copy[ind++] = val % 10;
    //         val /= 10;
    //     }
    // }
    copyAndFormat(a, a_copy);
    copyAndFormat(b, b_copy);
    
    printf("\na = ");
    for(unsigned int i = 0; i < a_bit_size; i++)
        printf("%d",a_copy[i]);
    
    printf("\nb = ");
    for(unsigned int i = 0; i < b_bit_size; i++)
        printf("%d",b_copy[i]);

    printf("\n");

    unsigned int pos = 0;
    unsigned int a_nb = 0, b_nb = 0;


    if (a_bit_size == b_bit_size) {
        unsigned int base = 1;

        for (unsigned int i = 0; i < a_bit_size; ++i) {
            a_nb += a_copy[i] * base;
            b_nb += b_copy[i]* base;
            base *= 10;
        }

        printf("a_nb = %d\n",a_nb);
        printf("b_nb = %d\n",b_nb);

        if(a_nb == b_nb)
            return 0;
        else{
            for (unsigned int i = 0; i < a_bit_size; i++)
                if (a_copy[i] != b_copy[i]) {
                    pos = i;
                    break;
                }
            unsigned int j = 0;
            if (a_nb > b_nb){
                for (unsigned int i = 0; i < a.size; i++){
                    for(unsigned int j = i; j < countDigits(a.value[i]); j++){
                        if (j == pos)
                            return (i + 1);
                    }
                }
            }
            else{
                for (unsigned int i = 0; i < a.size; i++){
                    for(unsigned int j = i; j < countDigits(a.value[i]); j++){
                        if (j == pos)
                            return -(i + 1);
                    }
                }
            }
        }
    } else if (a_bit_size > b_bit_size) {
        for (unsigned int i = 0; i < b_bit_size; i++)
            if (a_copy[i] != b_copy[i]) {
                pos = i;
                break;
            }
        unsigned int j = 0;
        for (unsigned int i = 0; i < a.size; i++) {
            for (j = i; j < a_bit_size; j++) {
                if (j == pos)
                    return (i + 1);
            }
        }
    } else {
        for (unsigned int i = 0; i < b_bit_size; i++)
            if (a_copy[i] != b_copy[i]) {
                pos = i;
                break;
            }
        unsigned int j = 0;
        for (unsigned int i = 0; i < a.size; i++) {
            for (j = i; j < a_bit_size; j++) {
                if (j == pos)
                    return -(i + 1);
            }
        }
    }
    free(a_copy);
    free(b_copy);
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

    printf("\nc avant = ");
    for(int i = c.size-1; i >= 0; i--)
        printf("%d",c.value[i]);

    printf("\nb avant = ");
    for(int i = b.size-1; i >= 0; i--)
        printf("%d",b.value[i]);

    printf("\ntmp avant = ");
    for(int i = tmp.size-1; i >= 0; i--)
        printf("%d",tmp.value[i]);

    printf("\ncmp(tmp, zero) = %d\n",cmp(tmp, zero));
    while (cmp(b, tmp) != 0) {
        c = add(c, a);
        tmp = add(tmp, one);

        printf("\nc après = ");
        for(int i = c.size-1; i >= 0; i--)
            printf("%d",c.value[i]);
        
        printf("\ntmp après = ");
        for(int i = tmp.size-1; i >= 0; i--)
            printf("%d",tmp.value[i]);

        printf("\none après = ");
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