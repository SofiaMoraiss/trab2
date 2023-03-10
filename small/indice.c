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
    if (arqNomeDoc == NULL)
    {
        printf("ERRO: Arquivo %s nao encontrado!\n", argv[1]);
        return 1; // VER SE VAI SAIR SEM FINALIZAR TUDO
    }

    l = Listas_ler_train(temp, arqNomeDoc);
    l = Listas_calcula_tf_idfs(l);
    Listas_gera_binario(l, argv[2]);
    Listas_imprime_saida(l);

    Listas_destroi(l);
    fclose(arqNomeDoc);

    return 0;
}
