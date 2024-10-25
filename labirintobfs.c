#include <stdio.h>
#include <stdlib.h>

typedef struct node { // Estrutura de um nó da lista de adjacências
    int vertice;
    struct node *prox;
} node;

// Declaração da função que converte o labirinto em lista de adjacências
void converterLabirintoParaListaAdj(int tam, int **lab, node* listaAdj[]);

// Função para converter coordenadas (x, y) para um índice único
int index(int x, int y, int tam);

// Função que adiciona uma adjacência na lista de adjacências
void adicionarAdjacente(node** lista, int adj);

// Função para realizar a busca em largura (BFS)
void bfs(int inicio, int final, int N, node* listaAdjacencias[]);

// Função para imprimir o caminho encontrado pelo BFS
void printCaminho(int inicio, int final, int* predecessor, int N, int* contador);

int main() {
    int tam, inicio, final;

    // Solicita o tamanho do labirinto
    printf("Informe o tamanho do labirinto\n");
    scanf("%d", &tam);

    // Alocando dinamicamente a matriz do labirinto
    int **labirinto = (int **)malloc(tam * sizeof(int *));
    for (int i = 0; i < tam; i++) {
        labirinto[i] = (int *)malloc(tam * sizeof(int));
    }

    // Lendo os valores do labirinto
    printf("Informe o labirinto\n");
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            scanf("%d", &labirinto[i][j]);
            if (labirinto[i][j] == 3) { // Posição inicial
                inicio = index(i, j, tam); // Converter (i, j) para índice
            }
            if (labirinto[i][j] == 2) { // Posição final
                final = index(i, j, tam); // Converter (i, j) para índice
            }
        }
    }

    // Alocando a lista de adjacências
    node **listaAdj = (node **)malloc(tam * tam * sizeof(node *));
    converterLabirintoParaListaAdj(tam, labirinto, listaAdj);

    // Executa a busca em largura para encontrar o caminho
    bfs(inicio, final, tam, listaAdj);

    // Liberação da memória alocada para o labirinto
    for (int i = 0; i < tam; i++) {
        free(labirinto[i]);
    }
    free(labirinto);

    // Liberação da memória alocada para a lista de adjacências
    for (int i = 0; i < tam * tam; i++) {
        node *temp = listaAdj[i];
        while (temp) {
            node *aux = temp->prox;
            free(temp);
            temp = aux;
        }
    }
    free(listaAdj);

    return 0;
}

// Função para converter um labirinto em uma lista de adjacências
void converterLabirintoParaListaAdj(int tam, int **lab, node* listaAdj[]) {
    int i, j;
    int u, v;

    // Inicializa a lista de adjacências com NULL
    for (i = 0; i < tam * tam; i++) {
        listaAdj[i] = NULL;
    }

    // Percorre cada célula do labirinto
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            // Se a célula não for uma parede (valor 1)
            if (lab[i][j] != 1) {
                u = index(i, j, tam); // Converte as coordenadas da célula atual para o índice do nó

                // Verifica se é possível conectar o nó atual (u) ao nó acima dele (v)
                if (i > 0 && lab[i - 1][j] != 1) { // Cima
                    v = index(i - 1, j, tam);
                    adicionarAdjacente(&listaAdj[u], v); // Adiciona v na lista de u
                    adicionarAdjacente(&listaAdj[v], u); // Adiciona u na lista de v (grafo não direcionado)
                }

                // Verifica se é possível conectar o nó atual (u) ao nó abaixo dele (v)
                if (i < tam - 1 && lab[i + 1][j] != 1) { // Baixo
                    v = index(i + 1, j, tam);
                    adicionarAdjacente(&listaAdj[u], v);
                    adicionarAdjacente(&listaAdj[v], u);
                }

                // Verifica se é possível conectar o nó atual (u) ao nó à esquerda dele (v)
                if (j > 0 && lab[i][j - 1] != 1) { // Esquerda
                    v = index(i, j - 1, tam);
                    adicionarAdjacente(&listaAdj[u], v);
                    adicionarAdjacente(&listaAdj[v], u);
                }

                // Verifica se é possível conectar o nó atual (u) ao nó à direita dele (v)
                if (j < tam - 1 && lab[i][j + 1] != 1) { // Direita
                    v = index(i, j + 1, tam);
                    adicionarAdjacente(&listaAdj[u], v);
                    adicionarAdjacente(&listaAdj[v], u);
                }
            }
        }
    }
}

// Função para converter coordenadas (x, y) para um índice único
int index(int x, int y, int tam) {
    return x * tam + y;
}

// Função que adiciona uma adjacência na lista de adjacências
void adicionarAdjacente(node** lista, int adj) {
    node* novoNo = (node*)malloc(sizeof(node));
    novoNo->vertice = adj;
    novoNo->prox = *lista;
    *lista = novoNo;
}

// Função para realizar a busca em largura (BFS)
void bfs(int inicio, int final, int N, node* listaAdjacencias[]) {
    int* visitado = (int*)calloc(N * N, sizeof(int)); // Array para marcar os nós visitados
    int* fila = (int*)malloc(N * N * sizeof(int)); // Fila para BFS
    int* predecessor = (int*)malloc(N * N * sizeof(int)); // Array para armazenar o predecessor de cada nó
    int frente = 0, tras = 0;

    fila[tras++] = inicio; // Adiciona o nó inicial na fila
    visitado[inicio] = 1; // Marca o nó inicial como visitado
    predecessor[inicio] = -1; // O nó inicial não tem predecessor

    // Loop principal do BFS
    while (frente < tras) {
        int atual = fila[frente++];

        // Verifica se chegou ao nó final
        if (atual == final) {
            printf("Caminho encontrado ate o vertice %d!\n", final);
            int contador = -1; // Inicializa o contador de vértices
            printCaminho(inicio, final, predecessor, N, &contador);
            printf("\nNumero de vertices no caminho: %d\n", contador);
            break;
        }

        // Explora todos os nós adjacentes
        node* temp = listaAdjacencias[atual];   
        while (temp) {
            int adj = temp->vertice;
            if (!visitado[adj]) {
                fila[tras++] = adj;
                visitado[adj] = 1;
                predecessor[adj] = atual;
            }
            temp = temp->prox;
        }
    }

    // Verifica se um caminho foi encontrado
    if (visitado[final] == 0) {
        printf("Nao foi possivel encontrar um caminho ate o vertice %d.\n", final);
    } else {
        int contador = -1;
        printf("Caminho do inicio ate o final: ");
        printCaminho(inicio, final, predecessor, N, &contador);
        printf("\nNumero de vertices no caminho: %d\n", contador);
    }

    // Libera a memória alocada
    free(visitado);
    free(fila);
    free(predecessor);
}

// Função para imprimir o caminho encontrado pelo BFS e contar o número de vértices
void printCaminho(int inicio, int final, int* predecessor, int N, int* contador) {
    if (inicio == final) {
        printf("%d ", inicio);
        (*contador)++; // Incrementa o contador
    } else if (predecessor[final] == -1) {
        printf("Nao ha caminho do inicio ao final.\n");
    } else {
        printCaminho(inicio, predecessor[final], predecessor, N, contador);
        printf("%d ", final);
        (*contador)++; // Incrementa o contador
    }
}
