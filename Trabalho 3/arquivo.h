#include <stdio.h>
#pragma once
#define __TAM_ARQUIVO 10000
#define __INTERVALO__IDS 40009

typedef struct tipoProduto{
    int id;
    char nome[50];
    char descricao[50];
    float preco;
} tipoProduto;

typedef struct tipoProduto produtoEstoque;

void produtoEstoqueImprime(produtoEstoque produto);
int produtoEstoqueBusca(FILE *arq, int indice);
int produtoEstoqueMaiorQue(FILE* arq, int preco);
