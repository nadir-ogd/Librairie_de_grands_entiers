#ifndef LIB_BIH_INT_H
#define LIB__BIG_INT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Type bigint */
typedef struct bigint {
unsigned int size; /* taille */
unsigned int *value; /* valeur */
} bigint;

/* External funcitons */
void initBigint(bigint *nb, const char *str);
unsigned int power(unsigned int base, unsigned int exponent);
int countDigits(unsigned int x);
void freebigint(bigint *num);

/* Operators */
int cmp(bigint a, bigint b);
bigint add(bigint a, bigint b);
bigint sub(bigint a, bigint b); 
bigint product(bigint a, bigint b);
void intdiv(bigint a, bigint b, bigint *quotient, bigint *modulo);
bigint pow2n(unsigned int n);

/* Input / Output */
void printbigint(bigint n);
char *biginttostr(bigint n);
bigint *strtobigint(char *s);
char *biginttosubstr(bigint n, int first, int last);

#endif
