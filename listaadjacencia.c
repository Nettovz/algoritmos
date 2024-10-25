#include <stdio.h>
#include <stdlib.h>

// Lista de adjacencia NAO DIRECIONAL
// Vertices da lista adjacente (pontos do grafo)
typedef struct node {
    int vertice;
    struct node *prox;
} node;

// Estrutura do grafo
// Possui um array de listas de adjacencia
// Cada indice do array representa as conexoes de um vertice
typedef struct {
    int numvertices;
    struct node **listaadjacencia;
} grafo;

grafo* criargrafo(int numvertices); // Funcao para criar um grafo com o numero de vertices informado
node* criarnode(int vertice); // Funcao para criar um no (vertice) dentro do grafo
void addnodeagrafo(grafo *g, int vertice1, int vertice2); // Funcao para adicionar uma aresta entre dois vertices
void print(grafo *grafocomplet); // Funcao para imprimir a lista de adjacencia

int main() {
    int numvertices;
    printf("Informe o numero de vertices:\n");
    scanf("%d", &numvertices);

    grafo *grafiscimoleto = criargrafo(numvertices);

    for (int i = 0; i < numvertices; i++) {
        int vertice1, vertice2;
        printf("Informe os vertices que ligam (vertice1 vertice2):\n");
        scanf("%d %d", &vertice1, &vertice2);
        addnodeagrafo(grafiscimoleto, vertice1, vertice2);
    }

    printf("Lista de adjacencia:\n");
    print(grafiscimoleto);

    return 0;
}

grafo* criargrafo(int numvertices) {
    grafo *grafocomplet = (grafo*)malloc(sizeof(grafo));
    grafocomplet->numvertices = numvertices;

    // Criacao do array de listas de adjacencia
    grafocomplet->listaadjacencia = (node**)malloc(numvertices * sizeof(node*));

    // Inicializacao das listas como NULL
    for (int i = 0; i < numvertices; i++) {
        grafocomplet->listaadjacencia[i] = NULL;
    }

    return grafocomplet;
}

node* criarnode(int vertice) {
    node *novo = (node*)malloc(sizeof(node));
    novo->vertice = vertice;
    novo->prox = NULL;

    return novo;
}

void addnodeagrafo(grafo *g, int vertice1, int vertice2) {
    // Adiciona vertice2 a lista de adjacencia de vertice1
    node *novo = criarnode(vertice2);
    novo->prox = g->listaadjacencia[vertice1];
    g->listaadjacencia[vertice1] = novo;

    // Adiciona vertice1 a lista de adjacencia de vertice2 (grafo nao direcional)
    node *novo2 = criarnode(vertice1);
    novo2->prox = g->listaadjacencia[vertice2];
    g->listaadjacencia[vertice2] = novo2;
}
\
// nessa funcao o grafo vai ser direcionado, pois . Não há mais a adição bidirecional.
/*
void addnodeagrafo(grafo *g, int vertice1, int vertice2) {
    // Adiciona vertice2 a lista de adjacencia de vertice1 (somente uma direcao)
    node *novo = criarnode(vertice2);
    novo->prox = g->listaadjacencia[vertice1];
    g->listaadjacencia[vertice1] = novo;
}*/
void print(grafo *grafocomplet) {
    for (int i = 0; i < grafocomplet->numvertices; i++) {
        node *aux = grafocomplet->listaadjacencia[i];
        printf("Adjacentes de %d: ", i);
        while (aux != NULL) {
            printf("%d -> ", aux->vertice);
            aux = aux->prox;
        }
        printf("NULL\n");
    }
}
