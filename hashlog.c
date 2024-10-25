#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Servidor {
    int timestamp;
    long long int ip;
    struct Servidor *prox;
} Servidor;

Servidor *ADD(Servidor *server, int *lmax, int *M, int *contador, int timestampFunc, long long int ipCliente);
int funcaoHashing(int t, int m);
Servidor *heashing(Servidor *server, int *M, int *rehashFlag);
int newsize(int *m);
void QRY(int *M, int *contador, int timestamp, Servidor *server);
Servidor *inserirOrdenado(Servidor *head, int timestampFunc, long long int ipCliente, int *contador);
int buscaBinaria(Servidor *arr, int size, int timestampFunc);
long long int buscaBinariaip(Servidor *arr, int size, int timestampFunc);
Servidor *converterListaParaArray(Servidor *head, int *size);
long long retornaip(Servidor *head, int timestampFunc);

int main() {
    int M, lmax, contador = 0;
    Servidor *server = NULL;
    char operacao[10];
    
    scanf("%d %d", &M, &lmax);
    
    server = (Servidor *)calloc(M, sizeof(Servidor)); // Lista inicial
    
    while (1) {
        scanf("%s", operacao);
        
        if (strcmp(operacao, "END") == 0) {
            break;
        }
        
        if (strcmp(operacao, "NEW") == 0) {
            int timestampFunc;
            long long int ipCliente;
            
            scanf("%d %lli", &timestampFunc, &ipCliente);
            
            server = ADD(server, &lmax, &M, &contador, timestampFunc, ipCliente);
            
        } else if (strcmp(operacao, "QRY") == 0) {
            int timestamp;
            scanf("%d", &timestamp);
            QRY(&M, &contador, timestamp, server);
        } else {
            printf("Operacao desconhecida\n");
        }
    }
    
    free(server);
    return 0;
}

Servidor *ADD(Servidor *server, int *lmax, int *M, int *contador, int timestampFunc, long long int ipCliente) {
    int rehashFlag = 0;
    int posicaoNaLista = 1;

    // Checa o rehashing
    if ((*contador) / (*M) > (*lmax)) {
        server = heashing(server, M, &rehashFlag);
    }

    // Recebe o índice
    int indice = funcaoHashing(timestampFunc, *M);
    
    Servidor *atual = &server[indice];

    // Sem colisão
    if (atual->timestamp == 0) {
        atual->timestamp = timestampFunc;
        atual->ip = ipCliente;
        atual->prox = NULL;
    } else {
        // Colisão: inserir ordenadamente na lista encadeada
        server[indice].prox = inserirOrdenado(server[indice].prox, timestampFunc, ipCliente, &posicaoNaLista);
        Servidor *tmp = server[indice].prox;
        posicaoNaLista = 1;

        while (tmp != NULL) {
            posicaoNaLista++;
            tmp = tmp->prox;
        }
    }

    printf("%d %d\n", indice, posicaoNaLista); // NEW
    (*contador)++;
    return server;
}

Servidor* inserirOrdenado(Servidor *head, int timestampFunc, long long int ipCliente, int *contador) {
    Servidor *novo = (Servidor *)malloc(sizeof(Servidor));
    novo->timestamp = timestampFunc;
    novo->ip = ipCliente;
    novo->prox = NULL;

    if (head == NULL || head->timestamp >= timestampFunc) {
        novo->prox = head;
        return novo;
    }

    Servidor *atual = head;
    while (atual->prox != NULL && atual->prox->timestamp < timestampFunc) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;

    return head;
}

int funcaoHashing(int t, int m) {
    return t % m;
}

int newsize(int *m) {
    return 2 * (*m) + 1;
}

Servidor *heashing(Servidor *server, int *M, int *rehashFlag) {
    int newtam = newsize(M);
    Servidor *novoServer = (Servidor *)calloc(newtam, sizeof(Servidor));

    for (int i = 0; i < *M; i++) {
        Servidor *atual = &server[i];
        
        while (atual != NULL) {
            if (atual->timestamp != 0) {
                int novoIndice = funcaoHashing(atual->timestamp, newtam);
                
                Servidor *novoElemento = (Servidor *)malloc(sizeof(Servidor));
                *novoElemento = *atual;
                novoElemento->prox = NULL;

                if (novoServer[novoIndice].timestamp == 0) {
                    novoServer[novoIndice] = *novoElemento;
                    novoServer[novoIndice].prox = NULL;
                } else {
                    novoServer[novoIndice].prox = inserirOrdenado(novoServer[novoIndice].prox, atual->timestamp, atual->ip, NULL);
                }
                free(novoElemento); // Libere a memória após usá-la
            }
            Servidor *temp = atual;
            atual = atual->prox;
            free(temp); // Libere a memória de atual
        }
    }

    free(server);

    *M = newtam;
    *rehashFlag = 1;

    return novoServer;
}

Servidor *converterListaParaArray(Servidor *head, int *size) {
    *size = 0;
    Servidor *atual = head;
    while (atual != NULL) {
        (*size)++;
        atual = atual->prox;
    }

    Servidor *arr = (Servidor *)malloc((*size) * sizeof(Servidor));
    atual = head;
    for (int i = 0; i < *size; i++) {
        arr[i] = *atual;
        atual = atual->prox;
    }

    return arr;
}

int buscaBinaria(Servidor *arr, int size, int timestampFunc) {
    int inicio = 0;
    int fim = size - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (arr[meio].timestamp == timestampFunc) {
            return meio;
        } else if (arr[meio].timestamp < timestampFunc) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1; // Timestamp não encontrado
}

int obterPosicaoListaEncadeada(Servidor *head, int timestampFunc) {
    int size = 0;
    Servidor *arr = converterListaParaArray(head, &size);
    int pos = buscaBinaria(arr, size, timestampFunc);
    free(arr);
    return (pos != -1) ? pos + 1 : -1; // +1 para ajuste de posição (começa em 1)
}

void QRY(int *M, int *contador, int timestamp, Servidor *server) {
    int indice = funcaoHashing(timestamp, *M);
    Servidor *atual = &server[indice];

    if (atual->timestamp == 0) {
        printf("-1 -1\n");
        return;
    } else {
        if (atual->prox != NULL && atual->timestamp != timestamp) {
            int posicaoNaLista = obterPosicaoListaEncadeada(atual->prox, timestamp);
            long long int ipachado = retornaip(atual->prox, timestamp);
            
            if (posicaoNaLista != -1) {
                printf("%lli %d\n", ipachado, posicaoNaLista);
            } else {
                printf("-1 -1\n");
            }
        } else if (atual->prox == NULL && atual->timestamp == timestamp || atual->prox != NULL && atual->timestamp == timestamp) {
            printf("%lli 0\n", atual->ip);
        } else {
            printf("-1 -1\n");
        }
    }
}

long long retornaip(Servidor *head, int timestampFunc) {
    int size = 0;
    Servidor *arr = converterListaParaArray(head, &size);
    long long int pos = buscaBinariaip(arr, size, timestampFunc);
    free(arr);
    return pos;
}

long long int buscaBinariaip(Servidor *arr, int size, int timestampFunc) {
    int inicio = 0;
    int fim = size - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (arr[meio].timestamp == timestampFunc) {
            return arr[meio].ip;
        } else if (arr[meio].timestamp < timestampFunc) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1; // Timestamp não encontrado   
}
