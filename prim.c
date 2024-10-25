#include <stdio.h>
#include <stdlib.h>


// estrutura para aramezar a aresta

typedef struct{
    int origem, dest, peso;
}aresta; //linha 

typedef struct{
   int vertices, arestas;
   struct aresta *arest;
}grafo; // estrutura que aramzena o numero de vertice e as arestas

// representar um subconjunto para a unionfind
struct Subconjunto {
    int pai;
    int rank;
};

grafo *criargrafo(int v, int E); //funcao para criar um grafo com o numero de arestas e vertices fornecidos

void kruskalMST(struct *grafo grafofinal);// funcao para encontrar a arvore geradora minima 

int comparaaresta(const void* a, const void* b); // Função ussada para ordenar as arestas por peso

int find(struct Subconjunto subconjuntos[], int i); // Função  para encontrar o conjunto de um elemento 

void Union(struct Subconjunto subconjuntos[], int x, int y);

int main (){
    int V, E;
  scanf("%d %d",&V,&E);

  grafo *grafofinal = criargrafo(V, E);

  for(int i = 0 ; i < V ; i++){
    int vert1, vert2, p;

    scanf("%d %d %d",&vert1,&vert2, &p);
    grafofinal->arest[i].origem = vert1;
    grafofinal->arest[i].dest = vert2;
    grafofinal->arest[i].peso = p;
  }

  kruskalMST(gragrafofinalfo);
    return 0;
}


grafo *criargrafo(int v, int E){//funcao para criar um grafo com o numero de arestas e vertices fornecidos

grafo *newgrafo = (grafo*)malloc(sizeof(grafo));
newgrafo->arest = (aresta*)malloc(E * sizeof(aresta))
newgrafo->vertices = v;
newgrafo->arestas = E;
   return newgrafo;
}

kruskalMST(struct *grafo grafofinal){

int v = Grafofinal->vertices;
aresta resultado[1000000]; //grafo resultante
int pesototal = 0; // peso total da mst
int e = 0;tal = 0; // peso total da mst
int e = 0;//contador de arestas na mst
int i = 0;//contador de arestas ordenadas

qsort(grafpofinal->arest, grafofinal->E, sizeof(struct aresta), comparaaresta);

Subconjunto *subconjuntos = (Subconjunto*)malloc(v * sizeof(Subconjunto)); 
    for (int j = 0; j < v; j++) {
        subconjuntos[j].pai = v;
        subconjuntos[j].rank = 0;
    }

// pegar  as arestas de menor peso
while (e < v && i < grafofinal->arestas){
    aresta proxaresta = grafofinal->arestas[i++];

        int x = find(subconjuntos, proxaresta.origem);
        int y = find(subconjuntos, proxaresta.dest);

         if (x != y) {
            resultado[e++] = proxaresta;
            Union(subconjuntos, x, y);
            pesototal += proxaresta.peso;  // Acumular o peso da aresta na MST
        }

         printf("Peso total da Árvore Geradora Mínima: %d\n", pesoTotal);
}


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











}
int comparaaresta(const void* a, const void* b){
    struct Aresta* a1 = (struct Aresta*)a;
    struct Aresta* a2 = (struct Aresta*)b;
    return a1->peso > a2->peso;
}

int find(struct Subconjunto subconjuntos[], int i) {
    if (subconjuntos[i].pai != i)
        subconjuntos[i].pai = find(subconjuntos, subconjuntos[i].pai);
    return subconjuntos[i].pai;
}