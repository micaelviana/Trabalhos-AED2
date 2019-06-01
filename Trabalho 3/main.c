#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arquivo.h"
#include "arvore_id.h"
#define TESTE 30

int main(){
    FILE* arq = fopen("base","r");
    arvoreId* arvore = arvoreIdInicializa();
    produtoEstoque produto;
    long int deslocamento;
    int i;
    clock_t ini,fim;
    double soma1,soma2,soma3;

    /*Criacao da arvore de indices*/
    for(i = 0; i < __TAM_ARQUIVO; i++){
        deslocamento = ftell(arq);
        fread(&produto,sizeof(tipoProduto),1,arq);
        arvore = arvoreIdInsere(arvore, produto.id, deslocamento);
    }

   soma1 = soma2 = soma3 = 0;
   fseek(arq, 0, SEEK_SET);
   for(i = 0; i < TESTE; i++){
       int chave = (rand() % __INTERVALO__IDS) + 1;
    
        ini = clock();
        produtoEstoqueBusca(arq, chave);
        fim = clock();
        soma1 += (double)(fim - ini) / CLOCKS_PER_SEC;

        ini = clock();
        arvoreIdBusca(arvore, chave);
        fim = clock();
        soma2 += (double)(fim - ini) / CLOCKS_PER_SEC;
   }

   printf("===============================================================\n");
   printf("Média Busca Sequencial no Arquivo\tMédia Busca Binária no Arquivo\n");
   printf("      %lf\t\t\t             %lf\n", soma1 / TESTE, soma2 / TESTE);
   printf("===============================================================\n\n");
}

/*
fseek(arq,resultadoBusca,SEEK_SET);
    fread(&produto, sizeof(produtoEstoque), 1, arq);

    produtoEstoqueImprime(produto);
*/