#include "./lib_big_int.h"

//External functions
int countDigits(unsigned int x) {
    if (x == 0) {
        return 1;
    }
    int count = 0;

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

void freebigint(bigint *num) {
    free(num->value);
    num->size = 0;
}

void initBigint(bigint *nb, const char *str) {
    int len = strlen(str);

    nb->size = (len + 8) / 9;//+8 : car la plus petite valeur pour len est 1
    nb->value = (unsigned int *)malloc(nb->size * sizeof(unsigned int));
    
    if (nb->value == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nb->size; i++) {
        nb->value[i] = 0;
    }

    int ind = 0;
    for (int i = len - 1; i >= 0; i -= 9) {
        
        unsigned int temp = 0;
        if (ind == nb->size-1){
            for (int j = 0; j < i+1; j++)
                temp = temp * 10 + (str[j] - '0'); 
        }
        else{
            int cond_j = i - 9;
            for (int j = cond_j + 1; j < cond_j + 10; j++)
                temp = temp * 10 + (str[j] - '0');
        }

        nb->value[ind] = temp;
        ind++;
    }
}


int cmp(bigint a, bigint b){
    unsigned int a_len = 0, b_len = 0;

    for (int i = 0; i < a.size; i++)
        a_len += countDigits(a.value[i]);
    for (int i = 0; i < b.size; i++)
        b_len += countDigits(b.value[i]);
    
    if (a_len > b_len){//a > b 
        for(int i = 0; i < b.size; i++){
            if (a.value[i] != b.value[i]){
                return (i+1);
            }
        }
        return b.size;
    }
    else if (a_len < b_len) {//b > a
        for(int i = 0; i < a.size; i++)
            if (a.value[i] != b.value[i])
                return -(i+1);
        return -(a.size);
    }
    else{//a > b ou b < a
        for(int i = 0; i < a.size; i++){
            if (a.value[i] > b.value[i])
                return (i+1);
            if (a.value[i] < b.value[i])
                return -(i+1);
        }
    }
    return 0; 
}

bigint add(bigint a, bigint b) {
    bigint c;
    unsigned int carry = 0, nb_digit_a, nb_digit_b, max_nb_digits;

    if(a.size >= b.size)
        c.size = a.size;
    else    
        c.size = b.size;

    c.value = (unsigned int *)malloc(c.size * sizeof(unsigned int));

    for (int i = 0; i < c.size; i++) {
        if (i < a.size)
            nb_digit_a = countDigits(a.value[i]);
        else
            nb_digit_a = 0;

        if (i < b.size)
            nb_digit_b = countDigits(b.value[i]);
        else
            nb_digit_b = 0;


        if (nb_digit_a > nb_digit_b) {
            max_nb_digits = nb_digit_a;
        } else {
            max_nb_digits = nb_digit_b;
        }

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
        if (carry > 0) {
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

    for (int i = 0; i < c.size; i++) {
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

bigint product(bigint a, bigint b) {
    bigint c;
    c.size = a.size + b.size;
    c.value = (unsigned int *)calloc(c.size, sizeof(unsigned int));

    for (unsigned int i = 0; i < a.size; i++) {
        unsigned int carry = 0;
        for (unsigned int j = 0; j < b.size; j++) {
            unsigned long long p = (unsigned long long)a.value[i] * b.value[j] + c.value[i + j] + carry;
            c.value[i + j] = p % power(10, 9);
            carry = p / power(10, 9);
        }
        c.value[i + b.size] += carry;
    }
    
    // Retirer les zéros non significatifs à gauche
    while (c.size >= 2 && c.value[c.size - 1] == 0){//la taille de bigint doit etre au moins 1
        c.size--;
        c.value = realloc(c.value, c.size * sizeof(unsigned int));
    }

    return c;
}


void intdiv(bigint a, bigint b, bigint *quotient, bigint *modulo) {
    if (cmp(a, b) == 0) {
        // a = b => (a/b = 1) et (a%b = 0)
        initBigint(quotient, "1");
        initBigint(modulo, "0");
    } else if (cmp(a, b) < 0) {
        // a < b => (a/b = 0) et (a%b = a)
        initBigint(quotient, "0");
        initBigint(modulo, biginttostr(a));
    } else {
        // a > b
        initBigint(quotient, "0");
        initBigint(modulo, biginttostr(a));

        bigint temp;
        initBigint(&temp, "0");

        for (int i = a.size - 1; i >= 0; i--) {
            unsigned int currentDigit = a.value[i];
            temp.size = 1;
            temp.value[0] = currentDigit;

            while (cmp(temp, b) >= 0) {
                // (*quotient) += power(10, 9 * i);
                unsigned int carry = 0;
                for (int j = 0; j <= i; j++) {
                    unsigned long long tempSum = (unsigned long long)(*quotient).value[j] +
                                                  (unsigned long long)carry +
                                                  (unsigned long long)power(10, 9 * i);
                    (*quotient).value[j] = (unsigned int)(tempSum % power(10, 9));
                    carry = (unsigned int)(tempSum / power(10, 9));
                }

                // temp = temp - b;
                bigint tempB = b;
                while (cmp(temp, tempB) >= 0) {
                    tempB = add(tempB, b);
                    temp = sub(temp, b);
                }
            }
        }

        for(int i = 0; i < temp.size; i++)
            modulo->value[i] = temp.value[i];

        // Supprimer les zéros non significatifs en tête du quotient
        while ((*quotient).size >= 2 && (*quotient).value[(*quotient).size - 1] == 0) {
            (*quotient).size--;
        }

        freebigint(&temp);
    }
}


bigint pow2n(unsigned int n){
    bigint p;
    double logBase2 = log2(power(2, 9));

    p.size = (int)ceil(n / logBase2);
    p.value = (unsigned int*) calloc(p.size, sizeof(unsigned int));
   
    if(p.value  == NULL){
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    p.value[0] = 1;
    for (unsigned int i = 1; i < p.size; i++)
        p.value[i] = 0;

    for (unsigned int i = 0; i < n; ++i) {
        unsigned int carry = 0;

        for (unsigned int j = 0; j < p.size; ++j) {
            unsigned long long tmp = (unsigned long long)p.value[j] * 2 + carry;
            p.value[j] = (unsigned int)(tmp % power(10, 9));
            carry = (unsigned int)(tmp / power(10, 9));
        }

        if (carry > 0)
            p.value[p.size++] = carry;
    }

    while (p.size > 1 && p.value[p.size - 1] == 0) {
        p.size--;
        p.value = (unsigned int*)realloc(p.value, p.size * sizeof(unsigned int));
        if (p.value == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    return p;     
} 

void printbigint(bigint n){
    for(int i = n.size-1; i >= 0; i--)
        printf("%u ",n.value[i]);
    printf("\n");
}

char *biginttostr(bigint n) {
    int len = 0;

    for (int i = 0; i < n.size; i++)
        len += countDigits(n.value[i]);

    char *str = (char *)malloc((len+1) * sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    int ind = 0;;
    for (int i = n.size - 1; i >= 0; --i){
        ind += sprintf(str + ind, "%u", n.value[i]);    
    }
    str[ind] = '\0'; 

    return str;
}


bigint *strtobigint(char *s){
    int len = strlen(s);
    
    bigint *n = (bigint *)malloc(sizeof(bigint));
    n->size = (len + 8) / 9;//+8 : car la plus petite valeur pour len est 1
    n->value = (unsigned int *)malloc(n->size * sizeof(unsigned int));
    
    if (n->value == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n->size; i++) {
        n->value[i] = 0;
    }

    int ind = n->size-1;
    
    for (int i = 0; i < len; i += 9) {
        unsigned int tmp = 0;
        int cond_j = (ind == 0) ? len : 9 * (i + 1);

        for (int j = i; j < cond_j; j++)
            tmp = tmp * 10 + (s[j] - '0');

        n->value[ind--] = tmp;
    }

    return n;
}

char *biginttosubstr(bigint n, int first, int last){
    if (first > last) {
        fprintf(stderr, "First doit etre inferieur ou égal à Last\n");
        exit(EXIT_FAILURE);
    }        
    
    int len = 0;
    for (int i = 0; i < n.size; i++)
        len += countDigits(n.value[i]);
    

    if (n.value == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    int ind = 0;
    char *str = (char *)malloc((last-first+1)*9*sizeof(char));
    
    for(int i = last; i >= first; i--)
        ind += sprintf(str + ind, "%u", n.value[i]);
    

    str[ind] = '\0';
    return str;
}