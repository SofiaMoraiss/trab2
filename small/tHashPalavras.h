#ifndef HASH_H
#define HASH_H

#include "tPalavra.h"

typedef struct hashPalavras tHashPalavras;
typedef struct listaPalavra tListaPalavra;
tHashPalavras * Hash_cria();
int Hash_cria_indice(char* );
void Hash_adiciona_palavra(tHashPalavras * , char* , int );
void Hash_imprime(tHashPalavras *, int);
tPalavra * Hash_get_palavra(tListaPalavra * );
tListaPalavra* Hash_get_no_palavra(tHashPalavras * , int ); // Recebe o indice hash e retorna o nó que inicia a lista encadeada daquela posicao
tListaPalavra ** Hash_get_lista_palavra(tHashPalavras * );
tListaPalavra* Hash_atribui_prox_no(tListaPalavra * );
int Hash_get_idc_max(tHashPalavras * );
void Hash_destroi(tHashPalavras * );

#endif
