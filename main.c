/* 
   NADIR OUAGUED
   M1 CHPS - 2023 / 2024

   << INSTRUCTIONS MAKEFILE >>
      - commande de compilation : make
      - commande d'execution    : ./main
      - commande de suppression des fichiers objet, executables : make clean 

   << STRUCTURE PROJET >>
      - include/  : contient les fichiers.h
      - obj/      : contient les fichiers.o
      - src/      : contient les fichiers.c
      - makefile  : contient les instructions de compilation & execution
      - main.c    : contient le code principal
*/

#include "lib_big_int.h"

int main(){
      printf("- Tests unitaires des fonctions de la premiere partie -\n");
      printf("- Tests unitaires des fonctions de la premiere partie -\n");
      
      unsigned int n;
      
      printf("Veuillez entrez le nombre n : ");
      scanf("%u", &n);

      int result = Mersenne(n);
      
      if (result) 
         printf("(2^%u - 1) est un nombre premier de Mersenne.\n", n);
      else
         printf("(2^%u - 1) n'est pas un nombre premier de Mersenne.\n", n);
    }