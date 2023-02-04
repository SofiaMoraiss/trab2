#include <stdio.h>
#include <string.h>

#include "tHashPalavras.h"
#include "tDocumento.h"
#include "tPalavra.h"
#include "tListas.h"

int main(int argc, char *argv[])
{
    tListas *l;
    char temp[125];
    FILE *arqNomeDoc = fopen(argv[1], "r");
    sscanf(argv[1], "%[^.].txt", temp);
    if (!arqNomeDoc)
    {
        printf("ARQUIVO NAO ENCONTRADO");
        exit(1);
    }

    // printf("\n ARGV 1: %s\n", argv[1]);
    // printf("\n ARGV 2: %s\n", argv[2]);

    if (arqNomeDoc == NULL)
    {
        printf("ERRO: Arquivo %s nao encontrado!\n", argv[1]);
        return 1; // VER SE VAI SAIR SEM FINALIZAR TUDO
    }

    l = Listas_ler_train(temp, arqNomeDoc);

   l = Listas_calcula_tf_idfs(l);

    Listas_gera_binario(l, argv[2]);

    Listas_imprime_relatorio_documentos(l);

    Listas_destroi(l);
    fclose(arqNomeDoc);

    return 0;
}
