//leitura dos dados#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int c;
    long long int conexao;
} Servidor;

Servidor* ADD(Servidor* serv, long long int conect, int client, int* tam);
void QRY(int cliente, const Servidor* serv, int tam);
Servidor* insertSorted(Servidor* arr, int* n, long long int conect, int client);
void printServers(const Servidor* serv, int tam);

int main() {
    Servidor* server = NULL;

    int tamanho = 0;
    char operacao[10];
    long long int timestamp;
    int cliente;
    
    while (1) {
        scanf("%s", operacao);
        
        if (strcmp(operacao, "END") == 0) {
            break;
        }
        
        if (strcmp(operacao, "NEW") == 0) {
            scanf("%d %lld", &cliente, &timestamp); //leitura dos dados
            server = ADD(server, timestamp, cliente, &tamanho);
        } else if (strcmp(operacao, "QRY") == 0) {
            int proc;
            scanf("%d", &proc);
            QRY(proc, server, tamanho);
        } else {
            printf("Operação errada %s\n", operacao); //debug
        }
    }
    
    free(server);
    return 0;
}

Servidor* ADD(Servidor* serv, long long int conect, int client, int* tam) {
    int novoTam = *tam + 1;
    Servidor* temp = (Servidor*)realloc(serv, novoTam * sizeof(Servidor)); //alocando no vetor, sempre aumentando de 1 em 1
    if (temp == NULL) {
        printf("Erro    \n");
        exit(1);
    }
    temp = insertSorted(temp, tam, conect, client); // inserindo de forma ordenada
    return temp;
}

Servidor* insertSorted(Servidor* arr, int* n, long long int conect, int client) {
    int i;
    for (i = *n - 1; (i >= 0 && arr[i].c > client); i--) {
        arr[i + 1] = arr[i];
    }
    arr[i + 1].conexao = conect;
    arr[i + 1].c = client;
    (*n)++;
    return arr;
}

void QRY(int cliente, const Servidor* serv, int tam) { //busca binaria
    int inicio = 0;
    int fim = tam - 1;
    int encontrado = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (serv[meio].c == cliente) {
            printf("%lld %d\n", serv[meio].conexao, meio);
            encontrado = 1;
            break;
        } else if (serv[meio].c < cliente) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (!encontrado) {
        printf("-1 -1\n");
    }
}

void printServers(const Servidor* serv, int tam) { //debug
    printf("Servidores atuais:\n");
    for (int i = 0; i < tam; i++) {
        printf("Conexao: %lld, Cliente: %d\n", serv[i].conexao, serv[i].c);
    }
}