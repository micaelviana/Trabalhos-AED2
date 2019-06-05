#include <stdio.h>
#include <stdbool.h>
#pragma once

#define __QUANT__PRODUTOS 10000
#define __INTERVALO__IDS 40009
#define __INTERVALO__REAL 100000000.0f
#define __NAO__ENCONTRADO -1
size_t __retorno__fread;

struct tipoProduto{
    int id;
    char nome[50];
    char descricao[50];
    float preco;
};

typedef struct tipoProduto produtoEstoque;

void produtoEstoqueImprime(produtoEstoque produto);
bool validaDeslocamento(long deslocamento);
long produtoEstoqueBusca(FILE *arq, int indice);
int produtoEstoqueBuscaMaiorQue(FILE* arq, float preco);
int produtoEstoqueBuscaMenorQue(FILE *arq, float preco);
int produtoEstoqueBuscaIntervalo(FILE *arq, float inicio, float fim);
