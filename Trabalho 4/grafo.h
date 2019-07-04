#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "fila.h"
#define and &&
#define or ||

enum{BRANCO,CINZA,PRETO};

typedef struct tipoNoGrafo{
	int vertices;
	int arestas;
	bool** adj;
}tipoGrafo;

bool** criaMatrizConexa(int ordem, float grau);
tipoGrafo* criaGrafo(int ordem, float grau);
tipoGrafo* apagaGrafo(tipoGrafo *grafo);
int* bfs(tipoGrafo *g, int raiz);
int* dfs(tipoGrafo* g);
void dfsVisita(tipoGrafo *g, char* cor,int u,int* r,int tempo);
void todosCaminhos(tipoGrafo *g, int raiz);
void visitaCaminhos(tipoGrafo *g, char *cor, int *caminho, int vertice, int tamSequencia);
bool temCiclo(tipoGrafo *g);
void imprimeDistancia(int *v, int ordem);
void imprimeGrafo(tipoGrafo* g);
float numeroArestas(int ordem,float grau);