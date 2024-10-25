#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
 
typedef struct vert {
    int valor;
    struct vert* next;
} vert;

void inserir(vert **vertice, int element);
vert* remover(vert **vertice);

int main() {
    vert *topo = NULL;

    // Testando as funções
    inserir(&topo, 10);
    inserir(&topo, 20);
    inserir(&topo, 30);

    vert* removido = remover(&topo);
    if(removido) {
        printf("Removido: %d\n", removido->valor);
        free(removido);
    }

    removido = remover(&topo);
    if(removido) {
        printf("Removido: %d\n", removido->valor);
        free(removido);
    }

    removido = remover(&topo);
    if(removido) {
        printf("Removido: %d\n", removido->valor);
        free(removido);
    }

    removido = remover(&topo);
    if(removido) {
        printf("Removido: %d\n", removido->valor);
        free(removido);
    }

    return 0;
}

void inserir(vert **vertice, int element) {
    vert *novo = (vert*) malloc(sizeof(vert));
 
    if(novo) {
        novo->valor = element;
        novo->next = NULL;
        if(*vertice == NULL) {
            *vertice = novo;
        } else {
            vert *aux = *vertice;
            while(aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = novo;
        }
        printf("Inserido: %d\n", element);
    } else {
        printf("Erro ao alocar memória!\n");
    }
}

vert* remover(vert **vertice) {
    vert *remover = NULL;
    if(*vertice) {
        remover = *vertice;
        *vertice = remover->next;
    } else {
        printf("Pilha vazia!\n");
    }
    return remover;
}
