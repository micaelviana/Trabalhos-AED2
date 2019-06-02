#pragma once
#define __QUANT__PRODUTOS 10000
#define __INTERVALO__IDS 40009
#define __INTERVALO__PRECOS 100000000.0f

struct tipoProduto{
    int id;
    char nome[50];
    char descricao[50];
    float preco;
};

typedef struct tipoProduto produtoEstoque;

void produtoEstoqueImprime(produtoEstoque produto);
int produtoEstoqueBusca(FILE *arq, int indice);
int produtoEstoqueBuscaMaiorQue(FILE* arq, float preco);
int produtoEstoqueBuscaMenorQue(FILE *arq, float preco);
int produtoEstoqueBuscaIntervalo(FILE *arq, float inicio, float fim);
