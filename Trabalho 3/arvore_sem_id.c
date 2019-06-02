#include <stdio.h>
#include <stdlib.h>
#include "arvore_sem_id.h"

arvIntervalo *arvIntervaloInicializa(arvIntervalo *raiz){
    return NULL;
}

arvIntervalo *arvIntervaloInsere(arvIntervalo *raiz, float preco){
    if (raiz == NULL){
        raiz = (arvIntervalo *)malloc(sizeof(arvIntervalo));
        raiz->preco = preco;
        raiz->esq = raiz->dir = NULL;
    }
    else if (preco < raiz->preco){
        raiz->esq = arvIntervaloInsere(raiz->esq, preco);
    }
    else if (preco > raiz->preco){
        raiz->dir = arvIntervaloInsere(raiz->dir, preco);
    }
    return raiz;
}

void arvIntervaloCaminha(arvIntervalo *raiz){
    if (raiz){
        arvIntervaloCaminha(raiz->esq);
        printf("%.2f ", raiz->preco);
        arvIntervaloCaminha(raiz->dir);
    }
}

int arvIntervaloBuscaMaiorQue(arvIntervalo* raiz, float preco){
    int resultadoEsq = 0, resultadoDir = 0;
    if (raiz == NULL)
        return 0;

    else if (raiz->preco <= preco)
        resultadoDir = arvIntervaloBuscaMaiorQue(raiz->dir, preco);

    else{
        resultadoEsq = arvIntervaloBuscaMaiorQue(raiz->esq, preco);
        resultadoDir = arvIntervaloBuscaMaiorQue(raiz->dir, preco);
    }
    return resultadoEsq + resultadoDir + (raiz->preco > preco);
}

int arvIntervaloBuscaMenorQue(arvIntervalo *raiz, float preco){
    int resultadoEsq = 0, resultadoDir = 0;
    if (raiz == NULL)
        return 0;

    else if (raiz->preco >= preco)
        resultadoEsq = arvIntervaloBuscaMenorQue(raiz->esq, preco);

    else{
        resultadoEsq = arvIntervaloBuscaMenorQue(raiz->esq, preco);
        resultadoDir = arvIntervaloBuscaMenorQue(raiz->dir, preco);
    }
    return resultadoEsq + resultadoDir + (raiz->preco < preco);
}

int arvIntervaloBuscaIntervalo(arvIntervalo *raiz, float inicio, float fim){
    int resultadoEsq = 0, resultadoDir = 0;
    if (raiz == NULL)
        return 0;

    else if (raiz->preco <= inicio)
        resultadoDir = arvIntervaloBuscaIntervalo(raiz->dir, inicio, fim);
    else if (raiz->preco >= fim)
        resultadoEsq = arvIntervaloBuscaIntervalo(raiz->esq, inicio, fim);
    else{
        resultadoEsq = arvIntervaloBuscaIntervalo(raiz->esq, inicio, fim);
        resultadoDir = arvIntervaloBuscaIntervalo(raiz->dir, inicio, fim);
    }
    return resultadoEsq + resultadoDir + ((raiz->preco > inicio) && (raiz->preco < fim));
}
