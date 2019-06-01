#pragma once

struct arvore_id{
    int indice;
    int deslocamento;
    struct arvore_id* esq;
    struct arvore_id* dir;
};

typedef struct arvore_id arvoreId;

arvoreId* arvoreIdInicializa();
arvoreId* arvoreIdInsere(arvoreId *raiz, int indice, int deslocamento);
void arvoreIdCaminha(arvoreId *raiz);
int arvoreIdBusca(arvoreId* raiz, int indice);
arvoreId* arvoreIdLibera(arvoreId* raiz);