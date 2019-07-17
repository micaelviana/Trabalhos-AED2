#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vetor.h"
#include "arvore.h"
#include "avl_tree.h"
#define TESTE 30
#define ITERACOES 10

int main(){
    printf("verificando se deu bom -3 \n");
    double soma1,soma2;
    clock_t ini,fim;
    int i,j;
    int chave;
    int scan;

    int *aux = array(__MAX__SIZE__TRAVERSALS);
    binaryTree* arvore = initialize();


    //-----------------------PRIMEIRA QUESTAO----------------------

    /*Eu preciso gerar 50 elementos aleatorios e distintos para arvore
    *O jeito de fazer isso eh somar o elemento randomico atual com o anterior,
    *so que isso gera um vetor ordenado. Entao a solucao gera um vetor ordenado pra ter certeza dos 50 elementos distintos, embaralha ele e joga pra arvore*/

    printf("=======================PRIMEIRA QUESTAO=======================================\n");
    arrayFillOrdered(aux,__MAX__SIZE__TRAVERSALS);
    shuffle(aux, __MAX__SIZE__TRAVERSALS);
    arvore = arrayToTree(arvore,aux,__MAX__SIZE__TRAVERSALS);

    printf("Caminhamento Pré-fixado\n");
    preOrder(arvore);
    printf("\n\n");

    printf("Caminhamento Central\n");
    inOrder(arvore);
    printf("\n\n");

    printf("Caminhamento Pós-fixado\n");
    postOrder(arvore);
    printf("\n\n");
    printf("\n\n\n\n");

    //-------------------SEGUNDA QUESTAO-------------------------
    printf("=======================SEGUNDA QUESTAO=======================================\n");
    arvore = freeTree(arvore);
    aux = reallocArray(aux, __MAX__SIZE__PACKS);//vou reaproveita-lo


    /*Gerar mais ou menos 200 elementos com algumas repeticoes*/
    arrayFillRandom(aux,__MAX__SIZE__PACKS);

    /*A funcao meio ordenado eh um Quick que tem uma decisao
    *No lugar de if(ini < fim) eu coloco (fim-ini > __RANDOM_FACTOR) isso deixa algumas partes baguncadas. O numero foi so uma escolha, quanto maior ele maior a bagunca*/
    
    meioOrdenado(aux,__MAX__SIZE__PACKS);

    printf("Valores que entram na arvore:\n");
    arrayPrint(aux,__MAX__SIZE__PACKS);
    printf("\n\n\n");

    arvore = arrayToTree(arvore,aux, __MAX__SIZE__PACKS);
    printf("Pacotes montados na ordem correta: \n");
    inOrder(arvore);
    printf("\n\n\n");
    printf("\n\n\n\n");

    //-------------------TERCEIRA QUESTAO-------------------------
    printf("=======================TERCEIRA QUESTAO=======================================\n");
    arvore = freeTree(arvore);

    //vou reutilizar ele agora pra 1m de elmentos
    aux = reallocArray(aux,__MAXSIZE);
    int* copia = array(__MAXSIZE);


    arrayFillOrdered(aux,__MAXSIZE);
    copyArray(copia,aux,__MAXSIZE);
    shuffle(copia,__MAXSIZE); 
    arvore = arrayToTree(arvore, copia, __MAXSIZE);
    freeArray(copia);

    srand(time(NULL));
    soma1 = soma2 = 0;
    for (i = 0; i < TESTE; i++){
        chave = (rand() % (__MAXSIZE) << 2) + 1;

        ini = clock();
        treeSearch(arvore, chave);
        fim = clock();
        soma1 += (double)(fim - ini) / CLOCKS_PER_SEC;

        ini = clock();
        binarySearch(aux, __MAXSIZE, chave);
        fim = clock();
        soma2 += (double)(fim - ini) / CLOCKS_PER_SEC;
    }
    freeArray(aux);

    printf("===============================================================\n");
    printf("Média Busca Binária na Arvore\t\tMédia Busca Binária no Vetor\n");
    printf("      %.10lf\t\t\t       %.10lf\n", soma1 / TESTE, soma2 / TESTE);
    printf("===============================================================\n\n");
    printf("\n\n\n\n");

    //-------------------QUARTA QUESTAO-------------------------
    printf("=======================QUARTA QUESTAO=======================================\n");
    int* v = array(__MAXSIZE);

    avl_tree* avl;
    make__avl__tree(&avl);
    arvore = freeTree(arvore);

    soma1 = soma2 = 0;
    printf("TEMPO DE CRIAÇÃO E ALTURA\n");
    for(i = 0; i < ITERACOES; i++){
        arrayFillOrdered(v,__MAXSIZE);
        shuffle(v,__MAXSIZE);

        printf("Iteracao %d\n",i+1);

        ini = clock();
        arvore = arrayToTree(arvore,v,__MAXSIZE);
        fim = clock();
        printf("Tempo de criação da árvore binária de busca: %lf",(double)(fim - ini) / CLOCKS_PER_SEC);
        printf("\n");
        printf("Altura da árvore binária: %d",treeHeight(arvore));
        printf("\n\n");

        ini = clock();
        avl = array__to__avl__tree(avl,v,__MAXSIZE);
        fim = clock();
        printf("Tempo de criação da árvore avl: %lf", (double)(fim - ini) / CLOCKS_PER_SEC);
        printf("\n");
        printf("Altura da árvore avl: %d", avl__tree__height(avl));
        printf("\n\n");
        
        arvore = freeTree(arvore);
        avl = avl__tree__erase(avl);
    }
    printf("\n\n\n");


    printf("TEMPO DE BUSCA NAS ARVORES\n");
    int *copia2 = array(__MAXSIZE);

    arrayFillOrdered(v, __MAXSIZE);
    copyArray(copia2, v, __MAXSIZE);
    shuffle(copia2, __MAXSIZE);
    arvore = arrayToTree(arvore, copia2, __MAXSIZE);
    avl = array__to__avl__tree(avl,copia2,__MAXSIZE);
    freeArray(copia2);
    freeArray(v);

    soma1 = soma2 = 0;
    for (i = 0; i < TESTE; i++){
        chave = (rand() % (__MAXSIZE) << 2) + 1;

        ini = clock();
        treeSearch(arvore, chave);
        fim = clock();
        soma1 += (double)(fim - ini) / CLOCKS_PER_SEC;

        ini = clock();
        avl__tree__search(avl,chave);
        fim = clock();
        soma2 += (double)(fim - ini) / CLOCKS_PER_SEC;
    }

    printf("===============================================================\n");
    printf("Média Busca Binária na Arvore\t\tMédia Busca Binária na Arvore AVL\n");
    printf("      %.10lf\t\t\t       %.10lf\n", soma1 / TESTE, soma2 / TESTE);
    printf("===============================================================\n\n");
    printf("\n\n\n\n");
}
