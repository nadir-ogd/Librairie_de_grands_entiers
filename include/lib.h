#ifndef LIB_H
#define LIB_H

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

/* Operators */
int cmp(bigint a, bigint b); /* Comparaison */
bigint add(bigint a, bigint b); /* Addition */
bigint sub(bigint a, bigint b); /* Soustraction (a >= b)*/
bigint product(bigint a, bigint b); /* Produit */
/* Division */
void intdiv(bigint a, bigint b, bigint *quotient, bigint *modulo);
bigint pow2n(unsigned int n); /* 2 puissance n */
/* Input / Output */
void printbigint(bigint n); /* Affichage sortie standard */
char *biginttostr(bigint n); /* Conversion bigint vers chaine */
bigint *strtobigint(char *s); /* Conversion chaine vers bigint */
/* Conversion bigint vers chaine */
/* Decimales entre first et last */
char *biginttosubstr(bigint n, int first, int last);

#endif
