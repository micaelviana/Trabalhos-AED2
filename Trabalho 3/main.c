#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arquivo.h"
#include "arvore_id.h"
#include "arvore_sem_id.h"
#include "hash.h"
#define TESTE 30

unsigned long desloc_atual;
unsigned int pos;
unsigned int colisoes = 0;

int main(){
    FILE *arq = fopen("base", "w+");
    FILE *arqTexto = fopen("out", "r");
    produtoEstoque produto;
    long deslocamento;
    int i;
    clock_t ini, fim;
    int chaveInteira;
    float chaveReal1, chaveReal2;
    double soma1, soma2, soma3, soma4, soma5, soma6;

    /*Criacao do arquivo binario a partir do arquivo texto e indexacao das arvores*/
    arvId *arvore = arvIdInicializa();
    arvIntervalo *arvoreEspaco = arvIntervaloInicializa();
    tipoNoHash *tabela = tabelaHashCriar(__HASH_SIZE);
        while (fscanf(arqTexto, "%d %*[:] %[^:] %*[:] %[^:] %*[:] %f", &produto.id,         produto.nome, produto.descricao, &produto.preco) != EOF){
            deslocamento = ftell(arq);
            fwrite(&produto, sizeof(produtoEstoque), 1, arq);
            arvore = arvIdInsere(arvore, produto.id, deslocamento);
            arvoreEspaco = arvIntervaloInsere(arvoreEspaco, produto.preco,deslocamento);
            tabelaHashInserir(produto,tabela);
    }
    fclose(arqTexto);

    fseek(arq,0,SEEK_SET);

    //-----------------------PRIMEIRA QUESTAO----------------------

    soma1 = soma2 = soma3 =  0;
    fseek(arq, 0, SEEK_SET);
    for (i = 0; i < TESTE; i++){
        chaveInteira = (rand() % __INTERVALO__IDS) + 1;

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        produtoEstoqueBusca(arq, chaveInteira);
        fim = clock();
        soma1 += (double)(fim - ini) / CLOCKS_PER_SEC;

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        arvIdBusca(arq, arvore, chaveInteira);
        fim = clock();
        soma2 += (double)(fim - ini) / CLOCKS_PER_SEC;

        fseek(arq,0,SEEK_SET);
        ini = clock();
        tabelaHashBuscarAcessar(arq,chaveInteira,tabela,pos);
        fim = clock();
        soma3 += (double)(fim - ini) / CLOCKS_PER_SEC;

        printf("\n\n");
    }

    printf("-----------------------PRIMEIRA QUESTAO----------------------\n");
    printf("===============================================================\n");
    printf("Média Busca Sequencial no Arquivo\tMédia Busca usando arvore no Arquivo\n");
    printf("      %.7lf\t\t\t             %.7lf\n", soma1 / TESTE, soma2 / TESTE);
    printf("            Média Busca usando Hash no arquivo\n");
    printf("                         %.7lf\n",soma3/TESTE);
    printf("===============================================================\n\n\n\n");
    printf("Quantidade de colisões = %u\n", colisoes);
    printf("Percentual de colisões = %.2f%%\n\n",colisoes*100.0f/__QUANT__PRODUTOS);


    //-----------------------SEGUNDA QUESTAO----------------------//

    fseek(arq,0,SEEK_SET);
    soma1 = soma2 = soma3 = soma4 = soma5 = soma6 = 0;
    for (i = 0; i < TESTE; i++){
        chaveReal1 = (rand()/ __INTERVALO__REAL) + 1.0f;
        chaveReal2 = (rand() / __INTERVALO__REAL) + 1.0f;

        /*Busca de maiores que*/
        
        fseek(arq, 0, SEEK_SET);
        ini = clock();
        produtoEstoqueBuscaMaiorQue(arq, chaveReal1);
        fim = clock();
        soma1 += (double)(fim - ini) / CLOCKS_PER_SEC;

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        arvIntervaloBuscaMaiorQue(arq, arvoreEspaco, chaveReal1);
        fim = clock();
        soma2 += (double)(fim - ini) / CLOCKS_PER_SEC;

        /*Busca de menores que*/

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        produtoEstoqueBuscaMenorQue(arq, chaveReal1);
        fim = clock();
        soma3 += (double)(fim - ini) / CLOCKS_PER_SEC;

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        arvIntervaloBuscaMenorQue(arq, arvoreEspaco, chaveReal1);
        fim = clock();
        soma4 += (double)(fim - ini) / CLOCKS_PER_SEC;

        // /*Busca por intervalos*/

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        produtoEstoqueBuscaIntervalo(arq, chaveReal1, chaveReal2);
        fim = clock();
        soma5 += (double)(fim - ini) / CLOCKS_PER_SEC;

        fseek(arq, 0, SEEK_SET);
        ini = clock();
        arvIntervaloBuscaIntervalo(arq, arvoreEspaco, chaveReal1, chaveReal2);
        fim = clock();
        soma6 += (double)(fim - ini) / CLOCKS_PER_SEC;
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