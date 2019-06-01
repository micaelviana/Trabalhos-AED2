#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vetor.h"
#include "arvore.h"
#define TESTE 30
// #include "avl.h"

int main(){
    double soma1,soma2;
    clock_t ini,fim;
    int i,j;
    int *aux = array(MAX_SIZE_CAMINHAMENTO);
    arv* arvore = criaArvore();


    //-----------------------PRIMEIRA QUESTAO----------------------

    /*Eu preciso gerar 50 elementos aleatorios e distintos para arvore
    *O jeito de fazer isso eh somar o elemento rancomico atual com o anterior
    *so que isso gera um vetor ordenado. Entao a solucao gera um vetor ordenado pra ter certeza dos 50 elementos distintos, embaralha ele e joga pra arvore*/
    array__fill__ordered(aux,MAX_SIZE_CAMINHAMENTO);
    embaralha(aux, MAX_SIZE_CAMINHAMENTO);
    arvore = vetorParaArvore(arvore,aux,MAX_SIZE_CAMINHAMENTO);

    // printf("Caminhamento Pré-fixado\n");
    // caminhaPrefix(arvore);
    // printf("\n\n");

    // printf("Caminhamento Central\n");
    // caminhaInfix(arvore);
    // printf("\n\n");

    // printf("Caminhamento Pós-fixado\n");
    // caminhaPosfix(arvore);
    // printf("\n\n");

    //-------------------SEGUNDA QUESTAO-------------------------

    arvore = liberaArvore(arvore);
    arvore = criaArvore();
    aux = realocaVetor(aux, MAX_SIZE_PACOTES);//vou reaproveita-lo


    /*Gerar mais ou menos 200 elementos com algumas repeticoes*/
    array__fill__random(aux,MAX_SIZE_PACOTES);

    /*A funcao meio ordenado eh um Quick que tem uma decisao
    *No lugar de if(ini < fim) eu coloco (fim-ini > 5) isso deixa algumas partes baguncadas. O numero foi so uma escolha, quanto maior ele maior a bagunca*/
    meioOrdenado(aux,MAX_SIZE_PACOTES);

    // printf("Valores que entram na arvore:\n");
    // array__print(aux,MAX_SIZE_PACOTES);
    // printf("\n\n\n");

    arvore = vetorParaArvore(arvore,aux, MAX_SIZE_PACOTES);
    // printf("Pacotes montados na ordem correta: \n");
    // caminhaInfix(arvore);
    // printf("\n\n\n");

    //-------------------TERCEIRA QUESTAO-------------------------

    /*Essa parte de liberar e criar de novo nem precisava, porque ja ta apontando pra
    NULL, so que fica mais bonito*/
    arvore = liberaArvore(arvore);
    arvore = criaArvore();

    //vou reutilizar ele agora pra 1m de elmentos
    aux = realocaVetor(aux,__MAXSIZE);
    int* copia = array(__MAXSIZE);


    array__fill__ordered(aux,__MAXSIZE);
    copiaVetor(copia,aux,__MAXSIZE);
    embaralha(copia,__MAXSIZE);
    arvore = vetorParaArvore(arvore, copia, __MAXSIZE);
    free__array(copia);

    srand(time(NULL));
    soma1 = soma2 = 0;
    for (i = 0; i < TESTE; i++){
        int chave = (rand() % (__MAXSIZE) << 2) + 1;

        ini = clock();
        buscaArvore(arvore, chave);
        fim = clock();
        soma1 += (double)(fim - ini) / CLOCKS_PER_SEC;

        ini = clock();
        binary__search(aux, __MAXSIZE, chave);
        fim = clock();
        soma2 += (double)(fim - ini) / CLOCKS_PER_SEC;
    }

    // printf("===============================================================\n");
    // printf("Média Busca Binária na Arvore\t\tMédia Busca Binária no Vetor\n");
    // printf("      %lf\t\t\t       %lf\n", soma1 / 30, soma2 / 30);
    // printf("===============================================================\n\n");
}