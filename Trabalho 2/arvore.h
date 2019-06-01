#include <stdbool.h>
#pragma once

#define MAX_SIZE_CAMINHAMENTO 50
#define MAX_SIZE_PACOTES 200
#define MAX_SIZE_BUSCA 1000000

struct tipoNo{
    int dado;
    struct tipoNo* esq;
    struct tipoNo* dir;
};

typedef struct tipoNo arv;

arv* criaArvore();
arv* insereArvore(arv*, int);
void caminhaPrefix(arv*);
void caminhaInfix(arv*);
void caminhaPosfix(arv*);
arv* vetorParaArvore(arv*, int*, int);
arv* liberaArvore(arv*);
bool buscaArvore(arv*,int);

