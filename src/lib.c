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

int cmp(bigint a, bigint b){
    if (a.size > b.size){//a > b 
        for(unsigned int i = 0; i < b.size; i++)
            if (a.value[i] != b.value[i])
                return i;
        return b.size;//cas ou b est contenu dans a
    }
    else if (a.size < b.size) {//b > a
        for(unsigned int i = 0; i < a.size; i++)
            if (a.value[i] != b.value[i])
                return -i;
        return -(a.size);//cas ou a est contenu dans b
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

// bigint add(bigint a, bigint b){
//     bigint c;
//     unsigned int carry = 0, nb_digit_a = 0, nb_digit_b = 0, max_nb_digits = 0;
//     if (a.size >= b.size){
//         c.size = a.size;
//         c.value = (unsigned int*)malloc(c.size * sizeof(unsigned int));

//         for (unsigned int i = 0; i < b.size; i++){
//             nb_digit_a = countDigits(a.value[i]);
//             nb_digit_b = countDigits(b.value[i]);
//             if (nb_digit_a > nb_digit_b)
//                 max_nb_digits = nb_digit_a;
//             else
//                 max_nb_digits = nb_digit_b;
            
//             printf("Pour a[%d] + b[%d] : %d + %d\n",i,i,a.value[i],b.value[i]);
//             printf("nb_digit_a  = %d\n",nb_digit_a);
//             printf("nb_digit_b  = %d\n",nb_digit_b);
//             printf("max_nb_digits  = %d\n",max_nb_digits);
//             c.value[i] = a.value[i] + b.value[i] + carry;

//             printf("c.value avant = %d\n",c.value[i]);

//             if (countDigits(c.value[i]) > max_nb_digits && i != c.size-1){
//                 carry = 1;
//                 c.value[i] = c.value[i] % power(10, max_nb_digits);;
//             }
//             else
//                 carry = 0;
            
//             printf("c.value après = %d\n",c.value[i]);

//         }

//         c.value[b.size] = a.value[b.size] + carry;
//         for (unsigned int i = b.size+1; i < c.size; i++)
//           c.value[i] = a.value[i];

//         printf("c = ");
//         for(int i = c.size-1; i >= 0; i--){
//              printf("%d",c.value[i]);
//         }
//     }
//     else{
//         c.size = a.size;
//         c.value = (unsigned int*)malloc(c.size * sizeof(unsigned int));
//         for (unsigned int i = 0; i < a.size; i++)
//             c.value[i] = a.value[i] + b.value[i];

//         for (unsigned int i = a.size; i < c.size; i++)
//             c.value[i] = b.value[i];
//     }
//     return c;
// }

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
        } else {
            borrow = 0;
        }

        c.value[i] = diff;
    }

    while (c.size > 1 && c.value[c.size - 1] == 0) {
        c.size--;
        c.value = realloc(c.value, c.size * sizeof(unsigned int));
    }

    return c;
}

bigint product(bigint a, bigint b){

}

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