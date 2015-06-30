#ifndef DIFERENCAFINITA_H
#define DIFERENCAFINITA_H

#include <armadillo>

//Struct que representa uma máscara para derivada backward
typedef struct back_mask_ {
    int val;
    int val_ant;
} back_mask;

//Struct que representa uma máscara para derivada forward
typedef struct forw_mask_ {
    int val;
    int val_prox;
} forw_mask;

//Struct que representa uma máscara para derivada central
typedef struct central_mask_ {
    int val;
    int val_ant;
    int val_prox;
} central_mask;



#endif // DIFERENCAFINITA_H
