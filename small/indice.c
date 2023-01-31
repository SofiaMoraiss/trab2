#include <stdio.h>
#include <string.h>
#include "tListas.h"
#include "tHashPalavras.h"

int main(int argc, char *argv[]) {

  tListas *l;
  char temp[125];
    FILE * arqDoc=fopen(argv[1],"r");
    sscanf(argv[1],"%[^.].txt",temp);
    if(!arqDoc){
            printf("ARQUIVO NAO ENCONTRADO");
            exit(1);
    }
    
  // printf("\n ARGV 1: %s\n", argv[1]);
  // printf("\n ARGV 2: %s\n", argv[2]);

  //FILE *arqListadosDocs = fopen(argv[1], "r");

  if (arqDoc == NULL) {
    printf("ERRO: Arquivo %s nao encontrado!\n", argv[1]);
    return 1; // VER SE VAI SAIR SEM FINALIZAR TUDO
  }

  l=Listas_ler_train(temp,arqDoc);

  Lista_destroi(l);

  fclose(arqDoc);

  return 0;
}
