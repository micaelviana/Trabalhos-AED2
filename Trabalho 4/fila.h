#include <stdio.h>
#include <stdlib.h>
#pragma once


typedef struct tipoNo{
    int dado;
    struct tipoNo *prox;
} tipoNo;

typedef struct{
    tipoNo *prim, *ult;
} tipoFila;


void criarFila(tipoFila *f);
void inserirFila(tipoFila *f, int dado);
void removerFila(tipoFila *f);