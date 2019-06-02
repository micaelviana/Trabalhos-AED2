#pragma once

struct arvore_id{
    int indice;
    int deslocamento;
    struct arvore_id* esq;
    struct arvore_id* dir;
};

typedef struct arvore_id arvId;

arvId* arvIdInicializa();
arvId* arvIdInsere(arvId *raiz, int indice, int deslocamento);
void arvIdCaminha(arvId *raiz);
int arvIdBusca(arvId* raiz, int indice);
arvId* arvIdLibera(arvId* raiz);