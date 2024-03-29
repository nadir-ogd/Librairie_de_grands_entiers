#include "./lib_big_int.h"

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

    //si size > 1 tous les blocs sont a 9 chiffres sauf le dernier(9 au plus)
    a_len += 9 * (a.size-1) + countDigits(a.value[a.size-1]);
    b_len += 9 * (b.size-1) + countDigits(b.value[b.size-1]);

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
        int signe, i = a.size-1;
        //Pour savoir qui le plus grand entre A et B avant de trouver la position du premier bloc différent
        while (i >= 0 && a.value[i] == b.value[i])
            i--;

        if (i >= 0)
            signe = (a.value[i] > b.value[i]) ? 1 : -1;
             
        for(int i = 0; i < a.size; i++)
            if (a.value[i] != b.value[i])
                return (i+1)*signe;
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

    if (cmp(a, b) < 0) { //a doit etre sup ou égal à b
        fprintf(stderr, "Erreur : a doit être supérieur ou égal à b pour la soustraction.\n");
        initBigint(&c, "-1");
        return c;
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
    while (c.size >= 2 && c.value[c.size - 1] == 0){//cond d'arret : la taille de bigint doit etre inf ou égal à 1
        c.size--;
        c.value = realloc(c.value, c.size * sizeof(unsigned int));
    }

    return c;
}


void intdiv(bigint a, bigint b, bigint *quotient, bigint *modulo){
     if (cmp(a, b) == 0) {// a = b => (a/b = 1) et (a%b = 0)
        initBigint(quotient, "1");
        initBigint(modulo, "0");
    } else if (cmp(a, b) < 0) {// a < b => (a/b = 0) et (a%b = a)
        initBigint(quotient, "0");
        initBigint(modulo, biginttostr(a));
    } else{//a > b => (a/b = q) et (a%b = r)
        bigint one;
        initBigint(&one, "1");
        initBigint(quotient, "0");
        initBigint(modulo, biginttostr(a));

        for(int i = 0; i < a.size; i++)
            modulo->value[i] = a.value[i];

        while(cmp(*modulo, b) >= 0){//ca prend plus de temps pour des a et b grands
            *quotient = add(*quotient, one);
            *modulo = sub(*modulo, b);
        }
    }

    // Supprimer les zéros non significatifs en tête du quotient
    while ((*quotient).size >= 2 && (*quotient).value[(*quotient).size - 1] == 0) {
        (*quotient).size--;
        (*quotient).value = (unsigned int *)realloc((*quotient).value, (*quotient).size * sizeof(unsigned int));
        
        if ((*quotient).value == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
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
        //cas d'une retenue
        if (carry > 0)
            p.value[p.size++] = carry;
    }

    // Supprimer les zéros non significatifs
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
    for(int i = n.size-1; i >= 0; i--){
        if(i == n.size-1)
            printf("%u ",n.value[i]);
        else 
            printf("%09u ",n.value[i]);
    }
    printf("\n");
}

char *biginttostr(bigint n) {
    int len = 0;

    len += 9 * (n.size-1) + countDigits(n.value[n.size-1]);

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

    int ind = 0;
    for (int i = len - 1; i >= 0; i -= 9) {
        
        unsigned int temp = 0;
        if (ind == n->size-1){
            for (int j = 0; j < i+1; j++)
                temp = temp * 10 + (s[j] - '0'); 
        }
        else{
            int cond_j = i - 9;
            for (int j = cond_j + 1; j < cond_j + 10; j++)
                temp = temp * 10 + (s[j] - '0');
        }

        n->value[ind] = temp;
        ind++;
    }

    return n;
}

char *biginttosubstr(bigint n, int first, int last){
    if (first > last) {
        fprintf(stderr, "First doit etre inferieur ou égal à Last\n");
        exit(EXIT_FAILURE);
    }        
    
    char *fullstr = biginttostr(n);
    int len = last - first + 1;

    char *substr = (char *)malloc((len + 1) * sizeof(char)); // +1 pour le '\0'
    if (substr == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    int ind = 0;
    for (int i = first; i <= last; i++) {
        substr[ind++] = fullstr[i];
    }

    substr[ind] = '\0';
    free(fullstr);

    return substr;
}

int Mersenne(unsigned int n) {
    bigint Mn, S, two, one;
    int result;
    initBigint(&Mn , "0");
    initBigint(&S, "4");//S(1) = 4
    initBigint(&two, "2");
    initBigint(&one, "1");

    // Calcul de M_n = 2^n - 1
    Mn = sub(pow2n(n), one);

    // Test de Lucas-Lehmer
    if (n > 2){
        for (unsigned int k = 2; k < n; k++) {
            bigint Sk = product(S, S);
            S = sub(Sk, two);
        }

        // Vérification si le résultat final est nul
        bigint q,r;
        intdiv(S, Mn, &q, &r);

        result = (r.size == 1 && r.value[0] == 0);
        freebigint(&r);
        freebigint(&q);
    }
    else{ //cas de 2^(n-1) = 3
        if(n == 2)
            result = 1;
        else//Cas particuliers pour 0 et 1 (non premiers)
            result = 0;
    }

    // Libération de la mémoire allouée
    freebigint(&Mn);
    freebigint(&S);
    freebigint(&two);
    freebigint(&one);

    return result;
}

char* randomString() {
    int longueur = rand() % 50 + 1;
    char* suite = (char*)malloc((longueur + 1) * sizeof(char));

    if (suite == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < longueur; ++i) {
        suite[i] = '0' + rand() % 10;
    }

    suite[longueur] = '\0';

    return suite;
}

void tests_1() {
    int nbFunctions = 9;//Toutes les fonctions sauf printbigint
    
    for(int i = 0; i < nbFunctions; i++){
        switch ((i)){//tester une fonction pour dans chaque case
        case 0:
            bigint A,B;
            initBigint(&A, randomString());
            initBigint(&B, randomString());
            printf("Testing cmp Function : \n");
            printf("A = ");
            printbigint(A);
            printf("B = ");
            printbigint(B);
            printf("cmp(A, B) = %d\n", cmp(A,B));
            break;
        
        case 1:
            printf("\nTesting add Function : \n");
            bigint C;
        
            printf("A = ");
            printbigint(A);
            printf("B = ");
            printbigint(B);

            C = add(A, B);
            printf("add(A, B) = C\n");
            printf("C = ");
            printbigint(C);
            break;
        
        case 2:
            printf("\nTesting sub Function : \n");

            printf("A = ");
            printbigint(A);
            printf("B = ");
            printbigint(B);

            C = sub(A, B);
            printf("sub(A, B) = C\n");
            printf("C = ");
            printbigint(C);
            break;

        case 3:
            printf("\nTesting product Function : \n");

            printf("A = ");
            printbigint(A);
            printf("B = ");
            printbigint(B);

            C = product(A, B);
            printf("product(A, B) = C\n");
            printf("C = ");
            printbigint(C);
            break;
        
        case 4:
            printf("\nTesting intdiv Function : \n");

            bigint q, r;
            //éviter le random car la division prend beaucoup de temps sur les longs nombres
            initBigint(&A, "11111111111111111111111");
            printf("A = ");
            printbigint(A);
            initBigint(&B, "1000000000000000000000");
            printf("B = ");
            printbigint(B);

            intdiv(A, B, &q, &r);
            printf("inddiv(A, B, q, r) :\n");
            printf("q = ");
            printbigint(q);

            printf("r = ");
            printbigint(r);

            freebigint(&q);
            freebigint(&r);
            break;
        
        case 5:
            printf("\nTesting pow2n Function : \n");

            unsigned int n = rand() % 1000;//On peut aller jusqu'à n = 1000000
            C = pow2n(n);
            printf("C = 2^%u\n",n);
            printf("C = ");
            printbigint(C);

            break;
        
        case 6:
            printf("\nTesting biginttostr Function : \n");
            char *s;

            initBigint(&A, randomString());
            printf("A = ");
            printbigint(A);

            printf("Convertion du bigint A -> string s\n");

            s = biginttostr(A);
            printf("s = %s\n",s);

            break;
        
        case 7:
            printf("\nTesting strtobigint Function : \n");
            bigint *F;
            s = randomString();
            printf("s = %s\n",s);
            
            printf("Convertion du string s -> Bigint F\n");
            F = strtobigint(s);

            printf("F = ");
            printbigint(*F);

            break;

        case 8:
            printf("\nTesting biginttosubstr Function : \n");

            int first, last;
            char *a_string = randomString();
            
            initBigint(&A, a_string);
            printf("A = ");
            printbigint(A);

            first = rand() % strlen(a_string);
            last = first + rand() % (strlen(a_string) - first);

            printf("str = String entre l'indice %d et %d\n",first, last);
            char *str = biginttosubstr(A, first, last);
            printf("str = %s\n",str);

            break;
        default:
            break;
        }    
    } 
}

void tests_2(){
    unsigned int n;
    printf("Testing Mersenne Function :\n\n");
    printf("Veuillez entrez le nombre n : ");
    scanf("%u", &n);

    int result = Mersenne(n);//ca prend plus de temps pour des n plus grand
      
    if (result) 
        printf("(2^%u - 1) est un nombre premier de Mersenne.\n", n);
    else
        printf("(2^%u - 1) n'est pas un nombre premier de Mersenne.\n", n);
}