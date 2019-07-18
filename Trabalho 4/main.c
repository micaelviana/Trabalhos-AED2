#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"
#define TESTE 20

void imprimeVetor(int* v,int tam){
    for(int i = 0; i < tam; i++)
        printf("%d ",v[i]);
    printf("\n");
}

char* imprimeResultadoCiclo(bool n){
    if(n)
        return "Sim";
    return "Nao";
}


int main(){
    int i;
    int raiz;
    int tamGrafo,percentualConexoes,maximo,minimo;
    int* resultadosBFS;
    int* resultadosDFS;
    double soma1,soma2;
    tipoGrafo* g;
    clock_t ini,fim;
    float graus[4] = {25,50,75,100};

    srand(time(NULL));

    /*--------------------------------PRIMEIRA QUESTAO----------------------------------*/

    printf("-----------------------PRIMEIRA QUESTAO----------------------\n");
    printf("===============================================================\n");
    printf("Criacao de grafos com diferentes tamanhos e graus de conectividade\n\n"); 

    for(i = 0; i < 10; i++){
        tamGrafo = 4 + (rand()%7);
        percentualConexoes = graus[i%4];

        printf("Grafo %d, Numero de vertices: %d, Numero de arestas: %.0f,Grau de Conectividade sorteado: %d%%\n",i+1,tamGrafo,numeroArestas(tamGrafo,percentualConexoes),percentualConexoes);
        g = criaGrafo(tamGrafo,percentualConexoes);
        imprimeGrafo(g);
        g = apagaGrafo(g);
    }



    /*-----------------------------------SEGUNDA/TERCEIRA QUESTAO-------------------------------*/

    printf("-----------------------SEGUNDA/TERCEIRA QUESTAO----------------------\n");
    printf("===============================================================\n");
    printf("Mostrar os niveis da arvore resultante da BFS e media do tempo de execucao\n\n");

    soma1 = soma2 = 0;
    for(i = 0; i < TESTE; i++){
        tamGrafo = 300 + (rand()%201);
        percentualConexoes = graus[i % 4];
        raiz = rand()%tamGrafo;

        g = criaGrafo(tamGrafo, percentualConexoes);

        printf("Grafo: %d, Numero de vertices: %d, Numero de arestas: %.0f, Grau de conectividade sorteado: %d%%\n", i + 1, tamGrafo, numeroArestas(tamGrafo, percentualConexoes),percentualConexoes);
        printf("Raiz sorteada para a BFS: %d\n",raiz);

        ini = clock();
        resultadosBFS = bfs(g,raiz);
        fim = clock();
        soma1 += (double)(fim - ini) / CLOCKS_PER_SEC;
        printf("BFS %d, Tempo: %.7lf\n",i+1,(double)(fim-ini)/CLOCKS_PER_SEC);

        ini = clock();
        resultadosDFS = dfs(g);
        fim = clock();
        soma2 += (double)(fim - ini) / CLOCKS_PER_SEC;
        printf("DFS %d, Tempo: %.7lf\n\n", i + 1, (double)(fim - ini) / CLOCKS_PER_SEC);


        printf("Resultados BFS\n");
        imprimeDistancia(resultadosBFS, tamGrafo);
        printf("\n");
        printf("Resultados DFS\n");
        imprimeVetor(resultadosDFS, tamGrafo);
        printf("\n\n");

        g = apagaGrafo(g);
    }

    printf("Media de tempo da BFS: %.7lf\n", soma1 / TESTE);
    printf("Media de tempo da DFS: %.7lf\n\n\n", soma2 / TESTE);




    /*-------------------------QUARTA QUESTAO--------------------------*/
    printf("-----------------------QUARTA QUESTAO----------------------\n");
    printf("===============================================================\n");
    printf("Mostrar a sequencia de vertices vistados a partir de uma origem na qual todos os vertices sao visitados sem repeticao\n\n");

    printf("Grafo: 1, Numero de vertices: 6, Numero de arestas: 11, Grau de conectividade sorteado: 75%%\n");
    printf("Raiz escolhida: 0\n\n");

    tamGrafo = 6;
    percentualConexoes = 75;
    g = criaGrafo(tamGrafo,percentualConexoes);
    imprimeGrafo(g);
    printf("\n");
    todosCaminhos(g,0);
    printf("\n");

    g = apagaGrafo(g);

    
    
    
    
    /*-------------------------QUINTA QUESTAO--------------------------*/
    printf("-----------------------QUINTA QUESTAO----------------------\n");
    printf("===============================================================\n");
    printf("Verificar se os grafos tem ou nao ciclo\n\n");

    /*O grafo de conexao minima com certeza nao tem ciclo, entao ao passar um valor pequeno de conexao a saida esperada eh que nao tem ciclo, nos demais casos varia */

    for (i = 0; i < TESTE; i++){
        tamGrafo = 300 + (rand() % 201);
        if(i%2 == 0)
            percentualConexoes = 100;
        else
            percentualConexoes = 0;

        g = criaGrafo(tamGrafo,percentualConexoes);

        printf("Grafo %d, Numero de vertices %d, Numero de arestas: %.0f, Grau de Conectividade sorteado: %d%%\n", i + 1, tamGrafo, numeroArestas(tamGrafo, percentualConexoes),percentualConexoes);

        printf("Tem ciclo: %s\n",imprimeResultadoCiclo(temCiclo(g)));

        g = apagaGrafo(g);
    }
}
