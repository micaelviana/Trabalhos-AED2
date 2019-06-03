#include "arquivo.h"
 
void produtoEstoqueImprime(produtoEstoque produto){
    printf("Identificador :%d\nNome: %s\nDescricao: %s\nPreco, %.2f\n",produto.id,produto.nome,produto.descricao,produto.preco);
}

bool validaDeslocamento(long deslocamento){
    return (deslocamento != -1);
}

long produtoEstoqueBusca(FILE* arq, int indice){

    long posicaoOriginal = ftell(arq);
    long deslocamento;
    produtoEstoque aux;

    deslocamento = ftell(arq);
    while (fread(&aux, sizeof(produtoEstoque), 1, arq) != 0){
        if (aux.id == indice){
            fseek(arq,posicaoOriginal,SEEK_SET);
            return deslocamento;
        }
        deslocamento = ftell(arq);
    }
    fseek(arq, posicaoOriginal, SEEK_SET);
    return -1;
}

int produtoEstoqueBuscaMaiorQue(FILE *arq, float preco){
    long posicaoOriginal = ftell(arq);
    int resultado = 0;
    produtoEstoque aux;

    while (fread(&aux, sizeof(produtoEstoque), 1, arq) != 0){
        if(aux.preco > preco)
            resultado++;
    }
    fseek(arq, posicaoOriginal, SEEK_SET);
    return resultado;
}

int produtoEstoqueBuscaMenorQue(FILE *arq, float preco){
    long posicaoOriginal = ftell(arq);
    int resultado = 0;
    produtoEstoque aux;

    while (fread(&aux, sizeof(produtoEstoque), 1, arq) != 0){
        if (aux.preco < preco)
            resultado++;
    }
    fseek(arq, posicaoOriginal, SEEK_SET);
    return resultado;
}

int produtoEstoqueBuscaIntervalo(FILE *arq, float inicio, float fim){
    long posicaoOriginal = ftell(arq);
    int resultado = 0;
    produtoEstoque aux;

    while (fread(&aux, sizeof(produtoEstoque), 1, arq) != 0){
        if ( (aux.preco > inicio) && (aux.preco < fim) )
            resultado++;
    }
    fseek(arq, posicaoOriginal, SEEK_SET);
    return resultado;
}