#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#pragma once

struct arvore_busca_intervalo{
    float preco;
    long deslocamento;
    struct arvore_busca_intervalo *esq;
    struct arvore_busca_intervalo *dir;
};

typedef struct arvore_busca_intervalo arvIntervalo;

arvIntervalo* arvIntervaloInicializa();
arvIntervalo* arvIntervaloInsere(arvIntervalo *raiz, float preco, long deslocamento);
void arvIntervaloCaminha(arvIntervalo* raiz);
int arvIntervaloBuscaMaiorQue(FILE *arq, arvIntervalo *raiz, float preco) ;
int arvIntervaloBuscaMenorQue(FILE *arq, arvIntervalo *raiz, float preco);
int arvIntervaloBuscaIntervalo(FILE* arq, arvIntervalo * raiz, float inicio, float fim);