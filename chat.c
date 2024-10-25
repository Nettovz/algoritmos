	
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Estrutura para armazenar uma aresta
struct Aresta {
    int origem, destino, peso;
};

// Estrutura para representar um grafo
struct Grafo {
    int V, E;  // V = vértices (cidades), E = arestas (trechos)
    struct Aresta* aresta;
};

// Cria um grafo com V vértices e E arestas
struct Grafo* criaGrafo(int V, int E) {
    struct Grafo* grafo = (struct Grafo*)malloc(sizeof(struct Grafo));
    grafo->V = V;
    grafo->E = E;
    grafo->aresta = (struct Aresta*)malloc(E * sizeof(struct Aresta));
    return grafo;
}

// Estrutura para representar um subconjunto para a Union-Find
struct Subconjunto {
    int pai;
    int rank;
};

// Função auxiliar para encontrar o conjunto de um elemento (utiliza compressão de caminho)
int find(struct Subconjunto subconjuntos[], int i) {
    if (subconjuntos[i].pai != i)
        subconjuntos[i].pai = find(subconjuntos, subconjuntos[i].pai);
    return subconjuntos[i].pai;
}

// Função auxiliar para unir dois subconjuntos (utiliza união por rank)
void Union(struct Subconjunto subconjuntos[], int x, int y) {
    int raizX = find(subconjuntos, x);
    int raizY = find(subconjuntos, y);

    if (subconjuntos[raizX].rank < subconjuntos[raizY].rank)
        subconjuntos[raizX].pai = raizY;
    else if (subconjuntos[raizX].rank > subconjuntos[raizY].rank)
        subconjuntos[raizY].pai = raizX;
    else {
        subconjuntos[raizY].pai = raizX;
        subconjuntos[raizX].rank++;
    }
}

// Função de comparação usada para ordenar as arestas por peso
int comparaArestas(const void* a, const void* b) {
    struct Aresta* a1 = (struct Aresta*)a;
    struct Aresta* a2 = (struct Aresta*)b;
    return a1->peso > a2->peso;
}

// Função para encontrar a Árvore Geradora Mínima usando o algoritmo de Kruskal
void kruskalMST(struct Grafo* grafo) {
    int V = grafo->V;
    struct Aresta resultado[MAX];  // Esta será a MST resultante
    int e = 0;  // Contador de arestas incluídas na MST
    int i = 0;  // Contador de arestas ordenadas
    int pesoTotal = 0; // Variável para acumular o peso total da MST

    // Passo 1: Ordenar todas as arestas em ordem crescente de peso
    qsort(grafo->aresta, grafo->E, sizeof(struct Aresta), comparaArestas);

    // Alocar memória para criar V subconjuntos
    struct Subconjunto* subconjuntos = (struct Subconjunto*)malloc(V * sizeof(struct Subconjunto));

    // Criar subconjuntos com um elemento em cada um
    for (int v = 0; v < V; v++) {
        subconjuntos[v].pai = v;
        subconjuntos[v].rank = 0;
    }

    // Passo 2: Selecionar as arestas de menor peso, garantindo que não formem ciclos
    while (e < V - 1 && i < grafo->E) {
        struct Aresta proximaAresta = grafo->aresta[i++];

        int x = find(subconjuntos, proximaAresta.origem);
        int y = find(subconjuntos, proximaAresta.destino);

        // Se incluir esta aresta não formar um ciclo, adicioná-la ao resultado
        if (x != y) {
            resultado[e++] = proximaAresta;
            Union(subconjuntos, x, y);
            pesoTotal += proximaAresta.peso;  // Acumular o peso da aresta na MST
        }
    }

    // Exibir o resultado da MST
    printf("Arestas na Árvore Geradora Mínima:\n");
    for (i = 0; i < e; i++)
        printf("%d -- %d == %d\n", resultado[i].origem, resultado[i].destino, resultado[i].peso);

    // Exibir o peso total da MST
    printf("Peso total da Árvore Geradora Mínima: %d\n", pesoTotal);

    free(subconjuntos);
}

int main() {
    int V;  // Número de cidades (vértices)
    int E;  // Número de trechos (arestas)
    
    // Ler o número de vértices e arestas
    scanf("%d %d", &V, &E);
    struct Grafo* grafo = criaGrafo(V, E);

    // Definindo os trechos (arestas) e seus respectivos custos (pesos)
    for (int i = 0; i < E; i++) {
        int are1, are2, peso;
        scanf("%d %d %d", &are1, &are2, &peso);
        grafo->aresta[i].origem = are1;
        grafo->aresta[i].destino = are2;
        grafo->aresta[i].peso = peso;
    }

    // Encontrar a Árvore Geradora Mínima
    kruskalMST(grafo);a

    // Liberar a memória alocada
    free(grafo->aresta);
    free(grafo);

    return 0;
}
