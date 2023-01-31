#ifndef HASH_H
#define HASH_H

#include "tPalavra.h"

typedef struct hashPalavras tHashPalavras;
typedef struct listaPalavra tListaPalavra;
tHashPalavras * Hash_cria();
void Hash_adiciona_palavra(tHashPalavras * hashPalavras, char* palavra, int documento);
void Hash_imprime(tHashPalavras * hashPalavras, int documento);
tPalavra * Hash_get_palavra(tListaPalavra * listaPalavra);
tListaPalavra* Hash_get_no_palavra(tHashPalavras * hash,int posicao);
tListaPalavra ** Hash_get_lista_palavra(tHashPalavras * hash);
tListaPalavra* Hash_atribui_prox_no(tListaPalavra * lista);
int Hash_get_idc_max(tHashPalavras * hash);
void Hash_destroi(tHashPalavras * h);

#endif
