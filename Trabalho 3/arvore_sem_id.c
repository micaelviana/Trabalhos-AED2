#include "arvore_sem_id.h"

arvIntervalo *arvIntervaloInicializa(){
    return NULL;
}

arvIntervalo *arvIntervaloInsere(arvIntervalo *raiz, float preco, long deslocamento){
    if (raiz == NULL){
        raiz = (arvIntervalo*) malloc(sizeof(arvIntervalo));
        raiz->preco = preco;
        raiz->deslocamento = deslocamento;
        raiz->esq = raiz->dir = NULL;
    }
    else if (preco < raiz->preco){
        raiz->esq = arvIntervaloInsere(raiz->esq, preco,deslocamento);
    }
    else{
        raiz->dir = arvIntervaloInsere(raiz->dir, preco,deslocamento);
    }
    return raiz;
}

void arvIntervaloCaminha(arvIntervalo *raiz){
    if (raiz){
        arvIntervaloCaminha(raiz->esq);
        printf("%.2f ", raiz->preco);
        arvIntervaloCaminha(raiz->dir);
    }
}

int arvIntervaloBuscaMaiorQue(FILE* arq, arvIntervalo* raiz, float preco){
    int resultadoEsq = 0, resultadoDir = 0, resultadoNo = 0;

    if (raiz == NULL)
        return 0;

    else if (raiz->preco <= preco)
        resultadoDir = arvIntervaloBuscaMaiorQue(arq,raiz->dir, preco);

    else{
        resultadoEsq = arvIntervaloBuscaMaiorQue(arq,raiz->esq, preco);
        resultadoDir = arvIntervaloBuscaMaiorQue(arq,raiz->dir, preco);
    }

    resultadoNo = (raiz->preco > preco);
    if(resultadoNo){
        produtoEstoque aux;
        fseek(arq,raiz->deslocamento,SEEK_SET);
        __retorno__fread = fread(&aux, sizeof(produtoEstoque), 1, arq);
    }
    return resultadoEsq + resultadoDir + resultadoNo;
}

int arvIntervaloBuscaMenorQue(FILE* arq, arvIntervalo *raiz, float preco){
    int resultadoEsq = 0, resultadoDir = 0, resultadoNo = 0;

    if (raiz == NULL)
        return 0;

    else if (raiz->preco >= preco)
        resultadoEsq = arvIntervaloBuscaMenorQue(arq,raiz->esq, preco);

    else{
        resultadoEsq = arvIntervaloBuscaMenorQue(arq,raiz->esq, preco);
        resultadoDir = arvIntervaloBuscaMenorQue(arq,raiz->dir, preco);
    }

    resultadoNo = (raiz->preco < preco);
    if (resultadoNo){
        produtoEstoque aux;
        fseek(arq, raiz->deslocamento, SEEK_SET);
        __retorno__fread = fread(&aux, sizeof(produtoEstoque), 1, arq);
    }
    return resultadoEsq + resultadoDir + resultadoNo;
}

int arvIntervaloBuscaIntervalo(FILE* arq , arvIntervalo *raiz, float inicio, float fim)
{
    int resultadoEsq = 0, resultadoDir = 0, resultadoNo = 0;
    if (raiz == NULL)
        return 0;

    else if (raiz->preco <= inicio)
        resultadoDir = arvIntervaloBuscaIntervalo(arq,raiz->dir, inicio, fim);
    else if (raiz->preco >= fim)
        resultadoEsq = arvIntervaloBuscaIntervalo(arq,raiz->esq, inicio, fim);
    else
    {
        resultadoEsq = arvIntervaloBuscaIntervalo(arq,raiz->esq, inicio, fim);
        resultadoDir = arvIntervaloBuscaIntervalo(arq,raiz->dir, inicio, fim);
    }

    resultadoNo = (raiz->preco > inicio && raiz->preco < fim);
    if (resultadoNo){
        produtoEstoque aux;
        fseek(arq,raiz->deslocamento,SEEK_SET);
        __retorno__fread = fread(&aux,sizeof(produtoEstoque),1,arq);
    }

    return resultadoEsq + resultadoDir + resultadoNo;
}
