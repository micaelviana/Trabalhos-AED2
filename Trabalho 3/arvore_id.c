#include "arvore_id.h"

arvId* arvIdInicializa(){
    return NULL;
}

arvId* arvIdInsere(arvId* raiz, int indice, long deslocamento){
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

long arvIdBusca(FILE *arq, arvId *raiz, int indice){
    if(raiz == NULL)
        return __NAO__ENCONTRADO;
    else if(indice < raiz->indice)
        return arvIdBusca(arq,raiz->esq, indice);
    else if(indice > raiz->indice)
        return arvIdBusca(arq,raiz->dir, indice);
    
    produtoEstoque aux;
    fseek(arq,raiz->deslocamento,SEEK_SET);
    __retorno__fread = fread(&aux, sizeof(produtoEstoque), 1, arq);
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