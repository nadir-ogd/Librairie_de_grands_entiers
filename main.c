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
      printf("<--------- Tests Fonctions Partie 1 --------->\n \n");
      tests_1();
      
      printf("\n<--------- Tests Fonctions Partie 2 --------->\n \n");
      tests_2(); 
    }