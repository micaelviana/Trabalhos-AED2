#include "fila.h"

void criarFila(tipoFila *f){
    f->prim = NULL;
    f->ult = NULL;
}

void inserirFila(tipoFila *f, int dado){
    tipoNo *aux;
    aux = (tipoNo *)malloc(sizeof(tipoNo));
    if (aux == NULL){
        exit(1);
    }
    aux->dado = dado;
    if (f->prim == NULL){
        aux->prox = f->prim;
        f->prim = aux;
        f->ult = aux;
    }
    else{
        f->ult->prox = aux;
        aux->prox = NULL;
        f->ult = aux;
    }
}

void removerFila(tipoFila *f){
    tipoNo *primeiro;
    primeiro = f->prim;
    if (primeiro != NULL){
        f->prim = primeiro->prox;
        free(primeiro);
    }
    else{
        exit(1);
    }
}