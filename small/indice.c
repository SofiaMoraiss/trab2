#include <stdio.h>
#include <string.h>

#include "tHashPalavras.h"
#include "tListas.h"

int main(int argc, char *argv[]) {
    tListas *l;
    char temp[125];
    FILE *arqNomeDoc = fopen(argv[1], "r");
    sscanf(argv[1], "%[^.].txt", temp);
    if (!arqNomeDoc) {
        printf("ARQUIVO NAO ENCONTRADO");
        exit(1);
    }

    // printf("\n ARGV 1: %s\n", argv[1]);
    // printf("\n ARGV 2: %s\n", argv[2]);

    // FILE *arqListadosDocs = fopen(argv[1], "r");

    if (arqNomeDoc == NULL) {
        printf("ERRO: Arquivo %s nao encontrado!\n", argv[1]);
        return 1;  // VER SE VAI SAIR SEM FINALIZAR TUDO
    }

    l = Listas_ler_train(temp, arqNomeDoc);

    Listas_ordena_vetor(l);
    Listas_gera_binario(l,argv[2]);
//    Lista_imprime_vet_palavras(l);

    //imprimeHash(hash, 999);

    Listas_destroi(l);
    fclose(arqNomeDoc);

    return 0;
}
