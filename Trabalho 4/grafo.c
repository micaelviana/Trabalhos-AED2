#include "grafo.h"

static int pre[100000];
static int pai[100000];

bool** criaMatrizConexa(int ordem, float grau){
    int i;
    /*Aloca a matriz */
    bool **matriz = (bool **)malloc(ordem * sizeof(bool *));
    for (i = 0; i < ordem; i++)
        matriz[i] = (bool *)calloc(ordem, sizeof(bool));


    /*Criar conexoes aleatorias*/
    srand(time(NULL));

    int maximo = (ordem * (ordem - 1)) / 2;
    int minimo = ordem - 1;
    int linha, coluna;

    /*Garante que eh conexo*/
    for (i = 1; i <= minimo; i++)
        matriz[i - 1][i] = matriz[i][i - 1] = true;

    int limite = (grau / 100 * maximo) - minimo;

    i = 0;
    while (i < limite){
        linha = rand() % ordem;
        coluna = rand() % ordem;

        if ((linha != coluna) and matriz[linha][coluna] == false){
            matriz[linha][coluna] = matriz[coluna][linha] = true;
            i++;
        }
    }

    return matriz;
}

// void imprimeMatriz(bool **matriz, int ordem){
//     int i, j;

//     for (i = 0; i < ordem; i++){
//         for (j = 0; j < ordem; j++)
//             printf("%d ", matriz[i][j]);
//         printf("\n");
//     }
// }

void imprimeGrafo(tipoGrafo* g){
    bool** matriz = g->adj;
    int ordem = g->vertices;

    int i, j;
    for (i = 0; i < ordem; i++){
        if (i == 0)
            printf(" ");
        printf("   %d", i);
    }
    printf("\n");

    for (i = 0; i < ordem; i++)
        printf("-----");

    for (i = 0; i < ordem; i++){
        printf("\n%d|  ", i);
        for (j = 0; j < ordem; j++){
            if (i < 10 and j == 0)
                printf(" ");
            if (j > 9)
                printf("%d    ", matriz[i][j]);
            else
                printf("%d   ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

tipoGrafo *criaGrafo(int ordem, float grau){
    tipoGrafo *g = (tipoGrafo *)malloc(sizeof(tipoGrafo));
    g->vertices = ordem;
    g->arestas = 0;
    g->adj = criaMatrizConexa(ordem,grau);
    return g;
}

tipoGrafo *apagaGrafo(tipoGrafo *grafo){
    free(grafo);
    return NULL;
}

int* bfs(tipoGrafo* g, int raiz){
    int u, j;
    char cor[g->vertices];
    int* distancia = (int*)malloc(g->vertices * sizeof(int));
    tipoFila f;

    criarFila(&f);
    memset(cor, BRANCO, sizeof(cor));

    cor[raiz] = CINZA;
    distancia[raiz] = 0;
    inserirFila(&f, raiz);
    while (f.prim != NULL){
        u = f.prim->dado; 
        for (j = 0; j < g->vertices; j++){
            if (g->adj[u][j] == true){
                if (cor[j] == BRANCO){
                    cor[j] = CINZA;
                    distancia[j] = distancia[u] + 1;
                    inserirFila(&f, j);
                }
            }
        }
        removerFila(&f);
        cor[u] = PRETO;
    }
    return distancia;
}

void imprimeDistancia(int* v, int ordem){

    /*Achar ate onde tem distancia*/
    int i,j;
    int limite = 0;
    for(i = 0; i < ordem ; i++)
        if(v[i] > limite)
            limite = v[i];


    /*Imprimir as distancias */
    for(i = 0; i <= limite; i++){
        printf("Distancia %d: ",i);
        for(j = 0; j < ordem; j++)
            if(v[j] == i)
                printf(" %d",j);
        printf("\n\n");
    }
}

bool temCiclo(tipoGrafo *g){
    dfs(g);

    int i, j; //i vertex, j vertice que tem conexao comigo

    for (i = 0; i < g->vertices; i++)
        for (j = 0; j < g->vertices; j++)
            if ((g->adj[i][j] == true) and (pre[i] > pre[j]) and (j != pai[i]))
                return true;
    return false;
}

int* dfs(tipoGrafo *g){
    char cor[g->vertices];
    memset(cor, BRANCO, sizeof(cor));

    int* resultadosDFS = (int*) malloc(g->vertices * sizeof(int));

    /*A estrategia que faz com que o grafo seja conexo garante que a partir da raiz 0
    todos os vertices sejam visitados, entao nao precisa de um for na DFS nesse trabalho, o que melhora um pouco o tempo */
    pai[0] = 0;
    dfsVisita(g,cor,0,resultadosDFS,0);

    return resultadosDFS;
}

//r de resultados
void dfsVisita(tipoGrafo *g, char *cor, int vertice,int* r,int tempo){ 
    // printf("%d ", vertice);
    r[tempo++] = vertice;
    pre[vertice] = tempo;

    cor[vertice] = CINZA;

    for (int i = 0; i < g->vertices; i++)
        if (g->adj[vertice][i] == true and cor[i] == BRANCO){
            pai[i] = vertice;
            dfsVisita(g, cor,i,r,tempo);
        }
    cor[vertice] = PRETO;
}

/*@author: Jackson Celestino */
void todosCaminhos(tipoGrafo *g, int raiz){
    char cor[g->vertices];
    int caminho[g->vertices];
    int tamSequencia = 0;

    memset(cor,BRANCO,sizeof(cor));

    visitaCaminhos(g, cor, caminho, raiz, tamSequencia);
}

void visitaCaminhos(tipoGrafo *g, char *cor, int *caminho, int vertice, int tamSequencia){ 
    int i, fim = 1;

    cor[vertice] = CINZA;
    caminho[tamSequencia] = vertice;

    for (i = 0; i < g->vertices; i++){
        if (g->adj[vertice][i] == true and cor[i] != CINZA){
            visitaCaminhos(g, cor, caminho, i, tamSequencia + 1);
            fim = 0;
        }
    }

    if (fim == 1 /*and  tamSequencia+1 == g->vertices*/){
        for (i = 0; i <= tamSequencia; i++)
            printf("%d ", caminho[i]);
        printf("\n");
    }
    cor[vertice] = PRETO;
}

float numeroArestas(int ordem, float grau){
    int minimo = ordem-1;//412
    int maximo = ordem*(ordem-1)/2;//85078

    int grauMinimo = minimo*100.0/maximo;

    if(grau < grauMinimo)
        return minimo;
    return grau/100.0*maximo;
}