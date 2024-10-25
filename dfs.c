#include <stdio.h>
#define MAX 100

//omplexidade: A busca em profundidade (DFS) tem uma complexidade de tempo de  𝑂(𝑉+𝐸)

typedef struct {
    int vertices, arestas;
    int matrizadj[MAX][MAX];
    int visitados[MAX];
} grafo;

void iniciamatriz(grafo* graph); // funcao para iniciar a matriz
void preencherarestas(grafo* graph); // funcao para inserir as arestas do grafo
void dfs(grafo *graph, int vert, int vertfinal);

int main() {
    grafo graph;

    // Inicializa a matriz e preenche as arestas
    iniciamatriz(&graph);
    preencherarestas(&graph);

    int vert, vertfinal;
    printf("Informe o vertice inicial para a procura e o vertice final:\n");
    scanf("%d %d", &vert, &vertfinal);

    dfs(&graph, vert, vertfinal);
 
    if (graph.visitados[vertfinal] == 0) {
        printf("Nao ha caminho do vertice inicial ao final.\n");
    }

    return 0;
}

void iniciamatriz(grafo *graph) {
    // Preenche a matriz com 0 e nenhum vertice visitado
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            graph->matrizadj[i][j] = 0;
        }
        graph->visitados[i] = 0; // Nenhum vertice visitado
    }
}

void preencherarestas(grafo *graph) {
    printf("Informe o numero de vertices:\n");
    scanf("%d", &graph->vertices);

    printf("Informe o numero de arestas:\n");
    scanf("%d", &graph->arestas);

    int vert1, vert2;
    for (int i = 0; i < graph->arestas; i++) {
        printf("Informe os vertices que ligam (vertice1 vertice2):\n");
        scanf("%d %d", &vert1, &vert2);
        graph->matrizadj[vert1][vert2] = 1;
        graph->matrizadj[vert2][vert1] = 1;
    }
}

void dfs(grafo *graph, int vert, int vertfinal) {
    graph->visitados[vert] = 1; // Vertice visitado
    printf("Vertice %d visitado\n", vert);

    for (int adj = 0; adj < graph->vertices; adj++) {
        if (graph->matrizadj[vert][adj] == 1 && graph->visitados[adj] == 0) {
            dfs(graph, adj, vertfinal); // Continuar a procurar em outros vertices
        }
    }

    if (graph->visitados[vertfinal] == 1) {
        printf("Vertice %d encontrado\n", vertfinal);
        return; // Caminho encontrado
    }
}
