#ifndef HASH_H
#define HASH_H

#include "tPalavra.h"

typedef struct hashPalavras tHashPalavras;
typedef struct listaPalavra tListaPalavra;
tHashPalavras * criaHashPalavras();
void adicionaPalavra(tHashPalavras * hashPalavras, char* palavra, int documento);
void imprimeHash(tHashPalavras * hashPalavras, int documento);
tPalavra * Obtem_palavra(tListaPalavra * listaPalavra);
tListaPalavra* ObtemNoPalavra(tHashPalavras * hash,int posicao);
tListaPalavra ** ObtemListaPalavra(tHashPalavras * hash);
tListaPalavra* AtribuiProxNo(tListaPalavra * lista);
int Obtem_idc_max(tHashPalavras * hash);
void destroiHashPalavras(tHashPalavras * h);

#endif
