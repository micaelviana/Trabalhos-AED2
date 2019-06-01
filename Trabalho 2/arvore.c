#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

arv* criaArvore(){
    return NULL;
}

arv* insereArvore(arv* __raiz, int __dado){
    if(__raiz == NULL){
        __raiz = (arv*) malloc(sizeof(arv));
        __raiz->dado = __dado;
        __raiz->esq = __raiz->dir = NULL;
    }
    else if(__dado < __raiz->dado){
        __raiz->esq = insereArvore(__raiz->esq,__dado);
    }
    else if (__dado > __raiz->dado){
        __raiz->dir = insereArvore(__raiz->dir, __dado);
    }
    return __raiz;
}

void caminhaPrefix(arv* __raiz){
    if(__raiz){
        printf("%d ",__raiz->dado);
        caminhaPrefix(__raiz->esq);
        caminhaPrefix(__raiz->dir);
    }
}

void caminhaInfix(arv *__raiz){
    if (__raiz){
        caminhaInfix(__raiz->esq);
        printf("%d ", __raiz->dado);
        caminhaInfix(__raiz->dir);
    }
}

void caminhaPosfix(arv *__raiz){
    if (__raiz){
        caminhaPosfix(__raiz->esq);
        caminhaPosfix(__raiz->dir);
        printf("%d ", __raiz->dado);
    }
}

arv *vetorParaArvore(arv *__raiz, int *__v, int __tam){
    for(int i = 0; i < __tam; i++)
        __raiz = insereArvore(__raiz,__v[i]);
    return __raiz;
}

arv* liberaArvore(arv* __raiz){
    if(__raiz){
        __raiz->esq = liberaArvore(__raiz->esq);
        __raiz->dir = liberaArvore(__raiz->dir);
        free(__raiz);
    }
    return NULL;
}

bool buscaArvore(arv* __raiz, int __chave){
    if(__raiz == NULL) return false;
    else if(__chave < __raiz->dado) return buscaArvore(__raiz->esq,__chave);
    else if(__chave < __raiz->dado) return buscaArvore(__raiz->dir,__chave);
    return true;
}
