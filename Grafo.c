#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0
typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
}ADJACENCIA;

typedef struct vertice{
    ADJACENCIA *cab;
}VERTICE;

typedef struct grafo{
    int vertices;
    int arestas;
    VERTICE *adj;
}GRAFO;

GRAFO *criaGrafo (int v){
    int i;

    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g -> vertices = v;
    g -> arestas = 0;
    g -> adj = (VERTICE *)malloc(v*sizeof(VERTICE));

    for (i=0; i<v;i++){
        g -> adj[i].cab=NULL;
    }
    return (g);
}

ADJACENCIA *criadAdj(int v, int peso){
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp -> vertice =v;
    temp -> peso = peso;
    temp -> prox = NULL;
    return(temp);
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p){
    if(!gr) return(false);
    if((vf<0)||(vf>=gr->vertices))return(false);
    if((vi<0)||(vi>=gr->vertices))return(false);
    
    ADJACENCIA *novo = criadAdj(vf,p);
    
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab=novo;
    gr->arestas++;
    return (true);
}


void imprime(GRAFO *gr){
    printf("Vertices: %d. Arestas: %d \n",gr->vertices,gr->arestas);
    int i;
    
    for(i = 0; i<gr->vertices; i++){
        printf("v%d:",i+1);
        ADJACENCIA *ad = gr->adj[i].cab;
        while (ad){
            printf("v%d(%d) ",ad->vertice+1,ad->peso);
            ad=ad->prox;
        }
        printf("\n");
    }
}

void matriz(GRAFO *gr){ 
    printf("\n\nMatriz de AdjacÃªncia:\n");
    int i;
    for (i = 0; i < gr->vertices; i++) {
        for (int j = 0; j < gr->vertices; j++) {
            int adjacencia = 0;
            ADJACENCIA *ad = gr->adj[i].cab;
            while (ad) {
                if (ad->vertice == j) {
                    adjacencia = ad->peso;
                }
                ad = ad->prox;
            }
            printf("%d\t", adjacencia);
        }
        printf("\n");
    }
}

int somaCaminhosRecursivo(GRAFO *gr, int inicio, int destino, int *visitados) {
    if(inicio == destino) {
        visitados[inicio] = 1;
        return 0;
    }

    visitados[inicio] = 1;
    ADJACENCIA *ad = gr->adj[inicio].cab;
    int somaCaminhos = 0;

    while(ad != NULL) {
        int proximoVertice = ad->vertice;
        int pesoAresta = ad->peso;

        if(!visitados[proximoVertice]) {
            int x = somaCaminhosRecursivo(gr, proximoVertice, destino, visitados);

            if(visitados[proximoVertice] == 1 || x > 0) {
                somaCaminhos += pesoAresta + x;
            }
        }
        ad = ad->prox;
    }

    visitados[inicio] = 0;
    return somaCaminhos;
}

int somaCaminhos(GRAFO *gr, int inicio, int destino) {
    int *visitados = (int *)malloc(gr->vertices * sizeof(int));
    int i;
    for (i = 0; i < gr->vertices; i++) {
        visitados[i] = 0;
    }
    
    int soma = somaCaminhosRecursivo(gr, inicio, destino, visitados);
    free(visitados);
    return soma;
}

int main (){
    GRAFO *graf = criaGrafo(5);
    
    criaAresta(graf, 0, 0, 4); 
    criaAresta(graf, 0, 2, 11);
    criaAresta(graf, 2, 1, 1);
    criaAresta(graf, 2, 3, 2);
    criaAresta(graf, 3, 1, 6);
    criaAresta(graf, 3, 4, 7);
    criaAresta(graf, 4, 1, 9);

    printf("Lista de AdjacÃªncia:\n");
    imprime(graf);
    matriz(graf);

    imprime(graf);
    printf("\nValor total do caminho: %d ",somaCaminhos(graf,0,4));

    return 0;
}
