#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arquivo.h"
#include "arvore_id.h"
#include "arvore_sem_id.h"
#define TESTE 30

int main(){
    FILE *arq = fopen("base", "w+");
    FILE *arqTexto = fopen("out", "r");
    produtoEstoque produto;
    long int deslocamento;
    int i;
    clock_t ini, fim;
    int chaveInteira;
    float chaveReal1, chaveReal2;
    double soma1, soma2, soma3, soma4, soma5, soma6;

    /*Criacao do arquivo binario a partir do arquivo texto e indexacao da arvore*/
    arvId *arvore = arvIdInicializa();
    while (fscanf(arqTexto, "%d %*[:] %[^:] %*[:] %[^:] %*[:] %f", &produto.id, produto.nome, produto.descricao, &produto.preco) != EOF){
        deslocamento = ftell(arq);
        fwrite(&produto, sizeof(produtoEstoque), 1, arq);
        arvore = arvIdInsere(arvore, produto.id, deslocamento);
    }
    fclose(arqTexto);

    //-----------------------PRIMEIRA QUESTAO----------------------

    soma1 = soma2 = 0;
    fseek(arq, 0, SEEK_SET);
    for (i = 0; i < TESTE; i++){
        chaveInteira = (rand() % __INTERVALO__IDS) + 1;

        ini = clock();
        produtoEstoqueBusca(arq, chaveInteira);
        fim = clock();
        soma1 += (double)(fim - ini) / CLOCKS_PER_SEC;

        ini = clock();
        arvIdBusca(arvore, chaveInteira);
        fim = clock();
        soma2 += (double)(fim - ini) / CLOCKS_PER_SEC;
    }

    printf("-----------------------PRIMEIRA QUESTAO----------------------\n");
    printf("===============================================================\n");
    printf("Média Busca Sequencial no Arquivo\tMédia Busca Binária no Arquivo\n");
    printf("      %lf\t\t\t             %lf\n", soma1 / TESTE, soma2 / TESTE);
    printf("===============================================================\n\n\n\n");

    //-----------------------SEGUNDA QUESTAO----------------------//

    /*Criacao da arvore de intervalos*/
    fseek(arq, 0, SEEK_SET);
    arvIntervalo* arvoreEspaco = arvIntervaloInicializa();
    for (i = 0; i < __QUANT__PRODUTOS; i++){
        deslocamento = ftell(arq);
        fread(&produto, sizeof(produtoEstoque), 1, arq);
        arvoreEspaco = arvIntervaloInsere(arvoreEspaco, produto.preco);
    }

    fseek(arq,0,SEEK_SET);

    soma1 = soma2 = soma3 = soma4 = soma5 = soma6 = 0;
    for (i = 0; i < TESTE; i++){
        chaveReal1 = (rand()/ __INTERVALO__PRECOS) + 1.0f;
        chaveReal2 = (rand() / __INTERVALO__PRECOS) + 1.0f;

        /*Busca de maiores que*/
        ini = clock();
        produtoEstoqueBuscaMaiorQue(arq,chaveReal1);
        fim = clock();
        soma1 += (double)(fim - ini) / CLOCKS_PER_SEC;

        ini = clock();
        arvIntervaloBuscaMaiorQue(arvoreEspaco, chaveReal1);
        fim = clock();
        soma2 += (double)(fim - ini) / CLOCKS_PER_SEC;

        /*Busca de menores que*/
        ini = clock();
        produtoEstoqueBuscaMenorQue(arq, chaveReal1);
        fim = clock();
        soma3 += (double)(fim - ini) / CLOCKS_PER_SEC;

        ini = clock();
        arvIntervaloBuscaMenorQue(arvoreEspaco, chaveReal1);
        fim = clock();
        soma4 += (double)(fim - ini) / CLOCKS_PER_SEC;

        /*Busca por intervalos*/
        ini = clock();
        produtoEstoqueBuscaIntervalo(arq, chaveReal1, chaveReal2);
        fim = clock();
        soma5 += (double)(fim - ini) / CLOCKS_PER_SEC;

        ini = clock();
        arvIntervaloBuscaIntervalo(arvoreEspaco, chaveReal1, chaveReal2);
        fim = clock();
        soma6 += (double)(fim - ini) / CLOCKS_PER_SEC;
    }

    printf("-----------------------SEGUNDA QUESTAO----------------------\n");

    printf("===============================================================\n");
    printf("Média Busca por maiores no Arquivo\tMédia Busca por maiores na Arvore\n");
    printf("      %.7lf\t\t\t             %.7lf\n", soma1 / TESTE, soma2 / TESTE);
    printf("===============================================================\n\n");
    printf("Média Busca por menores no Arquivo\tMédia Busca por menores na Arvore\n");
    printf("      %.7lf\t\t\t             %.7lf\n", soma3 / TESTE, soma4 / TESTE);
    printf("===============================================================\n\n");
    printf("Média Busca de intervalo no Arquivo\tMédia Busca de intervalo na Arvore\n");
    printf("      %.7lf\t\t\t             %.7lf\n", soma5 / TESTE, soma6 / TESTE);
}

/*
fseek(arq,resultadoBusca,SEEK_SET);
    fread(&produto, sizeof(produtoEstoque), 1, arq);

    produtoEstoqueImprime(produto);
*/