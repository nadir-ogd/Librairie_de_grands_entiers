#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int size;
    unsigned int *value;
} BigInt;

/* Fonction pour initialiser un BigInt à partir d'une chaîne de caractères */
void initBigInt(BigInt *num, const char *str) {
    int len = strlen(str);
    num->size = (len + 8) / 9;
    num->value = (unsigned int *)malloc(num->size * sizeof(unsigned int));
    if (num->value == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < num->size; ++i) {
        num->value[i] = 0;
    }

    int index = 0;
    for (int i = len - 1; i >= 0; i -= 9) {
        int temp = 0;
        for (int j = i - 8; j <= i; ++j) {
            if (j >= 0) {
                temp = temp * 10 + (str[j] - '0');
            }
        }
        num->value[index++] = temp;
    }
}

/* Fonction pour libérer la mémoire allouée pour un BigInt */
void freeBigInt(BigInt *num) {
    free(num->value);
    num->size = 0;
}

/* Fonction pour comparer deux BigInts */
int cmp(BigInt a, BigInt b) {
    if (a.size > b.size) return 1;
    if (a.size < b.size) return -1;

    for (int i = a.size - 1; i >= 0; --i) {
        if (a.value[i] > b.value[i]) return 1;
        if (a.value[i] < b.value[i]) return -1;
    }

    return 0;  // Les BigInts sont égaux
}

/* Fonction pour ajouter deux BigInts */
BigInt add(BigInt a, BigInt b) {
    BigInt result;
    result.size = (a.size > b.size ? a.size : b.size) + 1;
    result.value = (unsigned int *)malloc(result.size * sizeof(unsigned int));
    if (result.value == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    unsigned int carry = 0;
    for (unsigned int i = 0; i < result.size; ++i) {
        unsigned int sum = carry;
        if (i < a.size) sum += a.value[i];
        if (i < b.size) sum += b.value[i];

        result.value[i] = sum % 1000000000;
        carry = sum / 1000000000;
    }

    // Si le dernier calcul a généré une retenue, alors il faut agrandir le tableau
    if (result.value[result.size - 1] == 0) {
        result.size--;
        result.value = (unsigned int *)realloc(result.value, result.size * sizeof(unsigned int));
        if (result.value == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    return result;
}

/* Fonction pour soustraire deux BigInts (supposant a >= b) */
BigInt sub(BigInt a, BigInt b) {
    BigInt result;
    result.size = a.size;
    result.value = (unsigned int *)malloc(result.size * sizeof(unsigned int));
    if (result.value == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    int borrow = 0;
    for (unsigned int i = 0; i < result.size; ++i) {
        int diff = a.value[i] - borrow;
        if (i < b.size) diff -= b.value[i];

        if (diff < 0) {
            diff += 1000000000;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.value[i] = diff;
    }

    // Supprimer les zéros non significatifs en tête du résultat
    while (result.size > 1 && result.value[result.size - 1] == 0) {
        result.size--;
        result.value = (unsigned int *)realloc(result.value, result.size * sizeof(unsigned int));
        if (result.value == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    return result;
}

/* Fonction pour multiplier deux BigInts */
BigInt product(BigInt a, BigInt b) {
    BigInt result;
    result.size = a.size + b.size;
    result.value = (unsigned int *)calloc(result.size, sizeof(unsigned int));
    if (result.value == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < a.size; ++i) {
        unsigned int carry = 0;
        for (unsigned int j = 0; j < b.size || carry > 0; ++j) {
            unsigned long long product = result.value[i + j] +
                                          (unsigned long long)a.value[i] * (j < b.size ? b.value[j] : 0) + carry;

            result.value[i + j] = product % 1000000000;
            carry = product / 1000000000;
        }
    }

    // Supprimer les zéros non significatifs en tête du résultat
    while (result.size > 1 && result.value[result.size - 1] == 0) {
        result.size--;
        result.value = (unsigned int *)realloc(result.value, result.size * sizeof(unsigned int));
        if (result.value == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    return result;
}

/* Fonction pour diviser deux BigInts (a / b) avec le quotient et le reste */
void intdiv(BigInt a, BigInt b, BigInt *quotient, BigInt *modulo) {
    if (cmp(b, a) > 0) {
        // Cas particulier : si b > a, le quotient est 0 et le reste est a
        *quotient = (BigInt){1, (unsigned int *)calloc(1, sizeof(unsigned int))};
        *modulo = a;
        return;
    }

    *quotient = (BigInt){1, (unsigned int *)calloc(a.size - b.size + 1, sizeof(unsigned int))};
    *modulo = (BigInt){a.size, (unsigned int *)calloc(a.size, sizeof(unsigned int))};

    // Initialiser le modulo avec les chiffres de a
    for (unsigned int i = 0; i < a.size; ++i) {
        (*modulo).value[i] = a.value[i];
    }

    // Calculer le quotient et le reste
    for (int i = a.size - b.size; i >= 0; --i) {
        while (cmp(*modulo, b) >= 0) {
            (*quotient).value[i]++;
            *modulo = sub(*modulo, b);
        }

        if (i > 0) {
            // Déplacer le chiffre suivant dans le modulo
            (*modulo).value[i - 1] += 1000000000 * (*modulo).value[i];
            (*modulo).value[i] = 0;
        }
    }

    // Supprimer les zéros non significatifs en tête du quotient
    while ((*quotient).size > 1 && (*quotient).value[(*quotient).size - 1] == 0) {
        (*quotient).size--;
        (*quotient).value = (unsigned int *)realloc((*quotient).value, (*quotient).size * sizeof(unsigned int));
        if ((*quotient).value == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    // Supprimer les zéros non significatifs en tête du reste
    while ((*modulo).size > 1 && (*modulo).value[(*modulo).size - 1] == 0) {
        (*modulo).size--;
        (*modulo).value = (unsigned int *)realloc((*modulo).value, (*modulo).size * sizeof(unsigned int));
        if ((*modulo).value == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
    }
}

/* Fonction pour calculer 2 puissance n */
BigInt pow2n(unsigned int n) {
    BigInt result = {n / 9 + 1, (unsigned int *)calloc(n / 9 + 1, sizeof(unsigned int))};
    if (result.value == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    result.value[result.size - 1] = 1;
    n %= 9;

    // Multiplication par 2 puissance n (où n est compris entre 0 et 8)
    for (unsigned int i = 0; i < n; ++i) {
        for (unsigned int j = 0; j < result.size; ++j) {
            result.value[j] *= 2;
        }

        for (unsigned int j = 0; j < result.size - 1; ++j) {
            if (result.value[j] >= 1000000000) {
                result.value[j + 1] += result.value[j] / 1000000000;
                result.value[j] %= 1000000000;
            }
        }
    }

    // Supprimer les zéros non significatifs en tête du résultat
    while (result.size > 1 && result.value[result.size - 1] == 0) {
        result.size--;
        result.value = (unsigned int *)realloc(result.value, result.size * sizeof(unsigned int));
        if (result.value == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    return result;
}

/* Fonction pour imprimer un BigInt */
void printBigInt(BigInt num) {
    printf("%u", num.value[num.size - 1]);
    for (int i = num.size - 2; i >= 0; --i) {
        printf("%09u", num.value[i]);
    }
    printf("\n");
}

/* Fonction pour convertir un BigInt en chaîne de caractères */
char *biginttostr(BigInt num) {
    int totalDigits = (num.size - 1) * 9 + (num.value[num.size - 1] == 0 ? 0 : (int)(log10(num.value[num.size - 1]) + 1));
    char *str = (char *)malloc((totalDigits + 1) * sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    for (int i = num.size - 1; i >= 0; --i) {
        if (i == num.size - 1) {
            // Le chiffre le plus significatif n'a pas besoin de zéros non significatifs à gauche
            index += sprintf(str + index, "%u", num.value[i]);
        } else {
            // Remplir de zéros non significatifs pour les chiffres moins significatifs
            index += sprintf(str + index, "%09u", num.value[i]);
        }
    }

    str[index] = '\0';  // Ajouter le caractère de fin de chaîne

    return str;
}

/* Fonction pour convertir une chaîne de caractères en BigInt */
BigInt *strtobigint(char *s) {
    BigInt *num = (BigInt *)malloc(sizeof(BigInt));
    if (num == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    initBigInt(num, s);

    return num;
}

/* Fonction pour convertir un sous-ensemble de chiffres d'un BigInt en chaîne de caractères */
char *biginttosubstr(BigInt num, int first, int last) {
    int totalDigits = (num.size - 1) * 9 + (num.value[num.size - 1] == 0 ? 0 : (int)(log10(num.value[num.size - 1]) + 1));
    char *str = (char *)malloc((totalDigits + 1) * sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    for (int i = last; i >= first; --i) {
        if (i >= 0 && i < num.size) {
            if (i == num.size - 1) {
                // Le chiffre le plus significatif n'a pas besoin de zéros non significatifs à gauche
                index += sprintf(str + index, "%u", num.value[i]);
            } else {
                //
