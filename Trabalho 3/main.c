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
    long deslocamento, retornoImpressao;
    int i;
    clock_t ini, fim;
    int chaveInteira;
    float chaveReal1, chaveReal2;
    double soma1, soma2, soma3, soma4, soma5, soma6;

    /*Criacao do arquivo binario a partir do arquivo texto e indexacao das arvores*/
    arvId *arvore = arvIdInicializa();
    arvIntervalo *arvoreEspaco = arvIntervaloInicializa();
    while (fscanf(arqTexto, "%d %*[:] %[^:] %*[:] %[^:] %*[:] %f", &produto.id, produto.nome, produto.descricao, &produto.preco) != EOF){
        deslocamento = ftell(arq);
        fwrite(&produto, sizeof(produtoEstoque), 1, arq);
        arvore = arvIdInsere(arvore, produto.id, deslocamento);
        arvoreEspaco = arvIntervaloInsere(arvoreEspaco, produto.preco,deslocamento);
    }
    fclose(arqTexto);

    //-----------------------PRIMEIRA QUESTAO----------------------

    soma1 = soma2 = 0;
    fseek(arq, 0, SEEK_SET);
    for (i = 0; i < TESTE; i++){
        chaveInteira = (rand() % __INTERVALO__IDS) + 1;

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        retornoImpressao = produtoEstoqueBusca(arq, chaveInteira);
        fim = clock();
        printf("Arquivo,deslocamento encontrado = %ld\n", retornoImpressao);
        soma1 += (double)(fim - ini) / CLOCKS_PER_SEC;

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        retornoImpressao = arvIdBusca(arq, arvore, chaveInteira);
        fim = clock();
        printf("Arvore, deslocamento encontrado = %ld\n", retornoImpressao);
        soma2 += (double)(fim - ini) / CLOCKS_PER_SEC;

        printf("\n\n");
    }

    printf("-----------------------PRIMEIRA QUESTAO----------------------\n");
    printf("===============================================================\n");
    printf("Média Busca Sequencial no Arquivo\tMédia Busca Binária no Arquivo\n");
    printf("      %.7lf\t\t\t             %.7lf\n", soma1 / TESTE, soma2 / TESTE);
    printf("===============================================================\n\n\n\n");


    //-----------------------SEGUNDA QUESTAO----------------------//

    fseek(arq,0,SEEK_SET);
    soma1 = soma2 = soma3 = soma4 = soma5 = soma6 = 0;
    for (i = 0; i < TESTE; i++){
        chaveReal1 = (rand()/ __INTERVALO__REAL) + 1.0f;
        chaveReal2 = (rand() / __INTERVALO__REAL) + 1.0f;

        /*Busca de maiores que*/
        
        fseek(arq, 0, SEEK_SET);
        ini = clock();
        retornoImpressao = produtoEstoqueBuscaMaiorQue(arq, chaveReal1);
        fim = clock();
        printf("Arquivo, quant de maiores = %ld\n", retornoImpressao);
        soma1 += (double)(fim - ini) / CLOCKS_PER_SEC;

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        retornoImpressao = arvIntervaloBuscaMaiorQue(arq, arvoreEspaco, chaveReal1);
        fim = clock();
        printf("Arvore, quant de maiores = %ld\n", retornoImpressao);
        soma2 += (double)(fim - ini) / CLOCKS_PER_SEC;

        printf("\n\n");
        /*Busca de menores que*/

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        retornoImpressao = produtoEstoqueBuscaMenorQue(arq, chaveReal1);
        fim = clock();
        printf("Arquivo, quant de menores = %ld\n", retornoImpressao);
        soma3 += (double)(fim - ini) / CLOCKS_PER_SEC;

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        retornoImpressao = arvIntervaloBuscaMenorQue(arq, arvoreEspaco, chaveReal1);
        fim = clock();
        printf("Arvore, quant de menores = %ld\n", retornoImpressao);
        soma4 += (double)(fim - ini) / CLOCKS_PER_SEC;

        printf("\n\n");
        // /*Busca por intervalos*/

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        retornoImpressao = produtoEstoqueBuscaIntervalo(arq, chaveReal1, chaveReal2);
        fim = clock();
        printf("Arquivo, tam do intervalo = %ld\n", retornoImpressao);
        soma5 += (double)(fim - ini) / CLOCKS_PER_SEC;

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        retornoImpressao = arvIntervaloBuscaIntervalo(arq, arvoreEspaco, chaveReal1, chaveReal2);
        fim = clock();
        printf("Arvore, tamanho do intervalo = %ld\n", retornoImpressao);
        soma6 += (double)(fim - ini) / CLOCKS_PER_SEC;

        printf("\n\n");
    }

    fclose(arq);

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