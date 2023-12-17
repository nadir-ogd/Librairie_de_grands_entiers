#include "./lib.h"

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

bigint add(bigint a, bigint b){
    bigint c;
    if (a.size > b.size){
        c.size = a.size;
        c.value = (unsigned int*)malloc(c.size * sizeof(unsigned int));
        for (unsigned int i = 0; i < b.size; i++)
            c.value[i] = a.value[i] + b.value[i];

        for (unsigned int i = b.size; i < c.size; i++)
            c.value[i] = a.value[i];
    }
    else{
        c.size = a.size;
        c.value = (unsigned int*)malloc(c.size * sizeof(unsigned int));
        for (unsigned int i = 0; i < a.size; i++)
            c.value[i] = a.value[i] + b.value[i];

        for (unsigned int i = a.size; i < c.size; i++)
            c.value[i] = b.value[i];
    }
    return c;
}

bigint sub(bigint a, bigint b){
    bigint c;   
    if (cmp(a,b) >= 0){
        c.size = a.size;
        c.value = (unsigned int*)malloc(c.size * sizeof(unsigned int));
        for (unsigned int i = 0; i < b.size; i++)
            c.value[i] = a.value[i] - b.value[i];

        for (unsigned int i = b.size; i < c.size; i++)
            c.value[i] = a.value[i];
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