#ifndef HASH_H
#define HASH_H

#include "tPalavra.h"

typedef struct hashPalavras tHashPalavras;
typedef struct listaPalavra tListaPalavra;
tHashPalavras *Hash_cria();
int Hash_cria_indice(char *);
//adiciona palavra no hash
void Hash_adiciona_palavra(tHashPalavras *, char *, int);
void Hash_imprime(tHashPalavras *, int);
tPalavra *Hash_get_palavra(tListaPalavra *);
tListaPalavra *Hash_get_no_palavra(tHashPalavras *, int); // Recebe o indice hash e retorna o nó que inicia a lista encadeada daquela posicao
tListaPalavra **Hash_get_lista_palavra(tHashPalavras *);
tListaPalavra *Hash_atribui_prox_no(tListaPalavra *);
int Hash_get_idc_max(tHashPalavras *);
tPalavra *Hash_procura_palavra(char *, tHashPalavras *);
void Hash_destroi(tHashPalavras *);
int Hash_obtem_numBytes();
int Hash_obtem_qtdPalavras(tHashPalavras * );
tHashPalavras* Hash_recria(tHashPalavras *,tPalavra * );
void Hash_atribui_idcMax(tHashPalavras *,int );
void Listas_le_binario(char *,tHashPalavras * );
tHashPalavras * Hash_le_bin(FILE * );
void Hash_escreve_bin(tHashPalavras *hash, FILE *);
int Hash_get_qtdPalavras(tHashPalavras *);

#endif
