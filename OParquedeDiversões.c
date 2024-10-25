#include <stdio.h>
#define maxk 25000
#define maxb 100
int calcdiv(int s, int b, int t); // calculo da diversao
int main(){
 int n; //numero de brinquedos
  scanf("%d",&n);
  int s[maxb], b[maxb], c[maxb];

  //preencher os brinquedos
  for(int i = 0; i < n; i++){
    scanf("%d %d %d",&s[i],&b[i],&c[i]);
  }

  int visitas; //numero de visitas
  scanf("%d",&visitas); //visitas

  for(int v = 0; v < visitas; v++){

          int k; //creditos de cada corrida
        scanf("%d",&k);

        int tabeladinamica[maxk + 1] = {0}; //tabela de programacao dinamica

        //cada brinquedo
        for(int i = 0; i < n; i++){
          for(int t = 1;;t++){
            int diversao = calcdiv(s[i],b[i], t);
            if(diversao == 0){
              break;
            }

        for(int j = k; j >= c[i]; j--){
            if(tabeladinamica[j] > tabeladinamica[j - c[i]] + diversao){
                tabeladinamica[j] = tabeladinamica[j];
            }
            else{
                tabeladinamica[j] = tabeladinamica[j - c[i]] + diversao;
            }
          }
          }
        }

        printf("%d: %d\n", v, tabeladinamica[k]); //imprimir o resultado da visita v

  }
    return 0;
}

int calcdiv(int s, int b, int t){
    int f = s - (t - 1) * (t - 1) * b;
    //somente valores positivos
    if(f > 0){
        return f;
    }
    else{
        return 0;  
    }
}