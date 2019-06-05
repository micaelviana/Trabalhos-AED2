#include "arquivo.h"
 
void produtoEstoqueImprime(produtoEstoque produto){
    printf("Identificador :%d\nNome: %s\nDescricao: %s\nPreco, %.2f\n",produto.id,produto.nome,produto.descricao,produto.preco);
}

bool validaDeslocamento(long deslocamento){
    return (deslocamento != __NAO__ENCONTRADO);
}

long produtoEstoqueBusca(FILE* arq, int indice){

    long deslocamento;
    produtoEstoque aux;

    deslocamento = ftell(arq);
    while (fread(&aux, sizeof(produtoEstoque), 1, arq) != 0){
        if (aux.id == indice)
            return deslocamento;
        deslocamento = ftell(arq);
    }
    return __NAO__ENCONTRADO;
}

int produtoEstoqueBuscaMaiorQue(FILE *arq, float preco){
    int resultado = 0;
    produtoEstoque aux;

    while (fread(&aux, sizeof(produtoEstoque), 1, arq) != 0){
        if(aux.preco > preco)
            resultado++;
    }
    return resultado;
}

int produtoEstoqueBuscaMenorQue(FILE *arq, float preco){
    int resultado = 0;
    produtoEstoque aux;

    while (fread(&aux, sizeof(produtoEstoque), 1, arq) != 0){
        if (aux.preco < preco)
            resultado++;
    }
    return resultado;
}

int produtoEstoqueBuscaIntervalo(FILE *arq, float inicio, float fim){
    int resultado = 0;
    produtoEstoque aux;

    while (fread(&aux, sizeof(produtoEstoque), 1, arq) != 0){
        if ( (aux.preco > inicio) && (aux.preco < fim) )
            resultado++;
    }
    return resultado;
}