#ifndef LIB_BIH_INT_H
#define LIB__BIG_INT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* Type bigint */
typedef struct bigint {
unsigned int size; /* taille */
unsigned int *value; /* valeur */
} bigint;

/* -------- Part 1 Functions -------- */

/* Operators */
int cmp(bigint a, bigint b);
bigint add(bigint a, bigint b);
bigint sub(bigint a, bigint b); 
bigint product(bigint a, bigint b);
void intdiv(bigint a, bigint b, bigint *quotient, bigint *modulo);
bigint pow2n(unsigned int n);

/* Input & Output */
void printbigint(bigint n);
char *biginttostr(bigint n);
bigint *strtobigint(char *s);
char *biginttosubstr(bigint n, int first, int last);

/* External Functions */
void initBigint(bigint *nb, const char *str); //genère un bigint à partir d'un string (pareil comme strtobigint mais elle est de type void)
unsigned int power(unsigned int base, unsigned int exponent);//retourne base puissance exponent
int countDigits(unsigned int x);//calcule le nombre de chiffres de x
void freebigint(bigint *num);//libère la mémoire du bigint num


/* -------- Part 2 Function -------- */
int Mersenne(unsigned int n); //Retourne 1 si 2^n - 1 est un nombre premier de Mersenne, 0 sinon


/* -------- Tests Functions -------- */
char* randomString(); //genère des chaine de caracteres de taille maximale (50) pour les tests
void tests_1();  // teste toutes les fonctions de la premiere partie (random inputs)
void tests_2(); // teste toutes les fonctions de la deuxieme partie (radnom inputs)
#endif