#include <stdlib.h>
#include <stdio.h>

int main() {
    int numerovertices;
    printf("Informe o numero de vertices: \n");
    scanf("%d", &numerovertices);

    // Criando a matriz de adjacencia
    int matrizadj[numerovertices][numerovertices];
    for (int i = 0; i < numerovertices; i++) {
        for (int j = 0; j < numerovertices; j++) {
            matrizadj[i][j] = 0;
        }
    }

    int numarestas;
    printf("Informe o numero de arestas: \n");
    scanf("%d", &numarestas);

    int linha, colunas;

    // Preenchendo a matriz de adjacencia
    for (int i = 0; i < numarestas; i++) {
        printf("Informe as conexoes dos vertices (linha coluna): \n");
        scanf("%d %d", &linha, &colunas);
        matrizadj[linha][colunas] = 1;
        // matrizadj[colunas][linha] = 1; // Descomente esta linha se o grafo for não direcionado
    }

    // Imprimindo a matriz de adjacencia
    printf("Matriz de adjacencia:\n");
    for (int i = 0; i < numerovertices; i++) {
        for (int j = 0; j < numerovertices; j++) {
            printf("%d ", matrizadj[i][j]);
        }
        printf("\n");
    }

    return 0;
}
