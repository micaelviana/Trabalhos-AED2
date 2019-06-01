#include "arvore_id.h"
#include <stdio.h>
#include <stdlib.h>

arvoreId* arvoreIdInicializa(){
    return NULL;
}

arvoreId* arvoreIdInsere(arvoreId* raiz, int indice, int deslocamento){
    if(raiz == NULL){
        raiz = (arvoreId*) malloc(sizeof(arvoreId));
        raiz->indice = indice;
        raiz->deslocamento = deslocamento;
        raiz->esq = raiz->dir = NULL;
    }
    else if(indice < raiz->indice){
        raiz->esq = arvoreIdInsere(raiz->esq,indice,deslocamento);
    }
    else if (indice > raiz->indice){
        raiz->dir = arvoreIdInsere(raiz->dir, indice, deslocamento);
    }
    return raiz;
}

void arvoreIdCaminha(arvoreId *raiz){
    if(raiz){
        arvoreIdCaminha(raiz->esq);
        printf("%d ",raiz->indice);
        arvoreIdCaminha(raiz->dir);
    }
}

int arvoreIdBusca(arvoreId* raiz, int indice){
    if(raiz == NULL)
        return -1;
    else if(indice < raiz->indice)
        return arvoreIdBusca(raiz->esq, indice);
    else if(indice > raiz->indice)
        return arvoreIdBusca(raiz->dir, indice);
    return raiz->deslocamento;
}

arvoreId* arvoreIdLibera(arvoreId* raiz){
    if(raiz){
        arvoreIdLibera(raiz->esq);
        arvoreIdLibera(raiz->dir);
        free(raiz);
    }
    return NULL;
}