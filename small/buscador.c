#include <stdio.h>
#include <tListas.h>
#define BUSCA 1
#define CLAS 2
#define RELPAL 3
#define RELDOC 4
int main(int argc, char *argv[])
{
    FILE *arqIndices = fopen(argv[1], "rb");
    if (!arqIndices)
    {
        printf("Erro! não foi possivel encontrar o arquivo %s", argv[1]);
        return 1;
    }

    tHashPalavras * hash=Hash_le_bin(arqIndices);
    int *qtdDocsLidos=calloc(1,sizeof(int));
    tDocumento ** vetDocumentos=Documento_le_indice(arqIndices,qtdDocsLidos);

    int k=atoi(argv[2]);
    printf("k: %d\n", k);
    
    int escolha;
    char frase[100];
    printf("\n\nBem Vindo ao Minerador de notícias!\n");
    do
    {
        printf("\n\nEscolha uma opcao:\n\n1- BUSCA\n2- CLASSIFICA\n3- RELATORIO DE PALAVRAS\n4- RELATORIO DE DOCUMENTOS\n0- SAIR\n\n");
        scanf("%d", &escolha);
        scanf("%*c");

        switch (escolha)
        {
        case BUSCA:
            Listas_busca_noticia(hash, *qtdDocsLidos, vetDocumentos);
            break;
        case CLAS:
            Listas_classifica_noticia(hash, *qtdDocsLidos, vetDocumentos, k);
            break;
        case RELDOC:
            Listas_imprime_relatorio_documentos(hash, vetDocumentos, *qtdDocsLidos);
            break;
        case RELPAL:
            Listas_imprime_relatorio_palavra(hash);
            break;
        default:
            escolha = 0;
            break;
        }

    } while (escolha);
    Hash_destroi(hash);
    Documento_destroi_idc(vetDocumentos, *qtdDocsLidos);
    free(qtdDocsLidos);
    fclose(arqIndices);

    return 0;
}
