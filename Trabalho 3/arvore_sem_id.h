#include <stdio.h>
#include <stdlib.h>
#pragma once

struct arvore_busca_intervalo{
    float preco;
    struct arvore_busca_intervalo *esq;
    struct arvore_busca_intervalo *dir;
};

typedef struct arvore_busca_intervalo arvIntervalo;

arvIntervalo* arvIntervaloInicializa();
arvIntervalo* arvIntervaloInsere(arvIntervalo *raiz, float preco);
void arvIntervaloCaminha(arvIntervalo* raiz);
int arvIntervaloBuscaMaiorQue(arvIntervalo* raiz, float preco);
int arvIntervaloBuscaMenorQue(arvIntervalo *raiz, float preco);
int arvIntervaloBuscaIntervalo(arvIntervalo *raiz, float inicio, float fim);