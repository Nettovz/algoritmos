#include <stdio.h>
#include <stdlib.h> // Para usar malloc
#define MAX 100

typedef struct {
    int vertices, arestas;
    int matrizadj[MAX][MAX];
    int visitados[MAX];
} grafo;

typedef struct {
    int itens[MAX];
    int inicio, fim;
} fila;

// Declaração das funções
void iniciamatriz(grafo* graph);
void preencherarestas(grafo* graph);
fila* criarfila();
int verificafila(fila* f);
void inserirfila(fila* f, int vert);
int removerfila(fila* f); // Corrigido para retornar um int
void bfs(grafo* graph, int vert, int vertfinal);

int main() {
    grafo graph;

    // Inicializa a matriz e preenche as arestas
    iniciamatriz(&graph);
    preencherarestas(&graph);

    int vert, vertfinal;
    printf("Informe o vertice inicial para a procura e o vertice final:\n");
    scanf("%d %d", &vert, &vertfinal);

    bfs(&graph, vert, vertfinal);

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

fila* criarfila() {
    fila* f = (fila*) malloc(sizeof(fila));
    f->inicio = -1;
    f->fim = -1; // Corrigido
    return f;
}

int verificafila(fila* f) {
    if (f->inicio == -1) {
        return 1; // Fila vazia
    }
    return 0;
}

void inserirfila(fila* f, int vert) {
    if (f->fim == MAX - 1) { // Checa se a fila esta cheia
        printf("Fila cheia\n");
        return;
    }
    f->fim++; // Incrementa para adicionar o vertice no final da fila
    f->itens[f->fim] = vert;
    if (f->inicio == -1) {
        f->inicio = 0; // Define o início se for a primeira inserção
    }
}

int removerfila(fila* f) {
    int item;
    if (verificafila(f)) {
        printf("Fila vazia\n");
        return -1; // Indica que a fila está vazia
    }

    // Remove o elemento da frente
    item = f->itens[f->inicio];
    f->inicio++;

    // Se o início ultrapassar o fim, a fila está vazia
    if (f->inicio > f->fim) {
        f->inicio = f->fim = -1; // Redefine os índices para indicar que a fila está vazia
    }
    return item;
}

void bfs(grafo* graph, int vert, int vertfinal) {
    // Cria a fila
    fila* queu = criarfila();

    // Marca o vertice como visitado
    graph->visitados[vert] = 1;
    // Empilha o vertice
    inserirfila(queu, vert);

    printf("Vertice %d visitado\n", vert);

    while (!verificafila(queu)) { // Enquanto a fila nao estiver vazia
        int correntvert = removerfila(queu); // Remove o vertice da fila

        // Visita vertices adjacentes do correntvert
        for (int adj = 0; adj < graph->vertices; adj++) {
            if (graph->matrizadj[correntvert][adj] == 1 && graph->visitados[adj] == 0) {
                graph->visitados[adj] = 1;
                inserirfila(queu, adj);
                printf("Vertice %d visitado\n", adj);

                if (adj == vertfinal) {
                    printf("Caminho encontrado\n");
                    free(queu); // Libera a memória alocada para a fila
                    return;
                }
            }
        }
    }

    free(queu); // Libera a memória alocada para a fila
}
