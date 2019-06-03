#include "arvore_id.h"

arvId* arvIdInicializa(){
    return NULL;
}

arvId* arvIdInsere(arvId* raiz, int indice, int deslocamento){
    if(raiz == NULL){
        raiz = (arvId*) malloc(sizeof(arvId));
        raiz->indice = indice;
        raiz->deslocamento = deslocamento;
        raiz->esq = raiz->dir = NULL;
    }
    else if(indice < raiz->indice){
        raiz->esq = arvIdInsere(raiz->esq,indice,deslocamento);
    }
    else if (indice > raiz->indice){
        raiz->dir = arvIdInsere(raiz->dir, indice, deslocamento);
    }
    return raiz;
}

void arvIdCaminha(arvId *raiz){
    if(raiz){
        arvIdCaminha(raiz->esq);
        printf("%d ",raiz->indice);
        arvIdCaminha(raiz->dir);
    }
}

long arvIdBusca(arvId* raiz, int indice){
    if(raiz == NULL)
        return -1;
    else if(indice < raiz->indice)
        return arvIdBusca(raiz->esq, indice);
    else if(indice > raiz->indice)
        return arvIdBusca(raiz->dir, indice);
    return raiz->deslocamento;
}

arvId* arvIdLibera(arvId* raiz){
    if(raiz){
        arvIdLibera(raiz->esq);
        arvIdLibera(raiz->dir);
        free(raiz);
    }
    return NULL;
}