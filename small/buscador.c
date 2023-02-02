#include <stdio.h>
#include <tListas.h>
#
#define BUSCA 1
#define CLAS 2
#define RELPAL 3
#define RELDOC 4
int main(int argc, char * argv[]){
    FILE * arqIndices=fopen(argv[1],"rb");
    tHashPalavras * hash=calloc(1,Hash_obtem_numBytes());
    Listas_le_binario(argv[1],hash);
    //Hash_imprime(hash,0);
    //Listas_imprime_vet_palavras(lista);
    //LeIndices(arqIndices,lista);
    int escolha;
    do{
        printf("bem vindo ao buscador\n\n");
        printf("Escolha uma opcao:\n\n1- BUSCA\n2- CLASSIFICA\n3- RELATORIO");
        scanf("%d",&escolha);

        char frase[100];
        switch (escolha)
        {
        case BUSCA:
            scanf("%[^\n]\n",frase);
            //Listas_busca_noticia(frase,lista);
            break;
        
        default:
            break;
        }

    }while(escolha);
    free(hash);
    fclose(arqIndices);

    return 0;
}


