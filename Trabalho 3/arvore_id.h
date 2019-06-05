#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#pragma once

struct arvore_id{
    int indice;
    long deslocamento;
    struct arvore_id* esq;
    struct arvore_id* dir;
};

typedef struct arvore_id arvId;

arvId* arvIdInicializa();
arvId* arvIdInsere(arvId *raiz, int indice, long deslocamento);
void arvIdCaminha(arvId *raiz);
long arvIdBusca(FILE* arq,arvId* raiz, int indice);
arvId* arvIdLibera(arvId* raiz);