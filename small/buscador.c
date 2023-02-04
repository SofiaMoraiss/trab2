#include <stdio.h>
#include <tListas.h>
#
#define BUSCA 1
#define CLAS 2
#define RELPAL 3
#define RELDOC 4
int main(int argc, char * argv[]){
    FILE * arqIndices=fopen(argv[1],"rb");

    tHashPalavras * hash=Hash_le_bin(arqIndices);
    int *qtdDocsLidos=calloc(1,sizeof(int));
    tDocumento ** vetDocumentos=Documento_le_indice(arqIndices,qtdDocsLidos);
    // for(int i=0;i<*qtdDocsLidos;i++){
    //     Documento_imprime_palavras(vetDocumentos[i]);
    // }
    int escolha;
        char frase[100];
    do{
        printf("bem vindo ao buscador\n\n");
        printf("Escolha uma opcao:\n\n1- BUSCA\n2- CLASSIFICA\n3- RELATORIO\n");
        scanf("%d",&escolha);
        scanf("%*c");
        

        switch (escolha)
        {
        case BUSCA:
            Listas_busca_noticia(hash,*qtdDocsLidos);
            break;
        
        default:
            break;
        }

    }while(escolha);
    Hash_destroi(hash);
    Documento_destroi_idc(vetDocumentos,*qtdDocsLidos);
    free(qtdDocsLidos);
    fclose(arqIndices);

    return 0;
}


