#ifndef HASH_H
#define HASH_H

#include "tPalavra.h"

typedef struct hashPalavras tHashPalavras;

tHashPalavras * criaHashPalavras();
void adicionaPalavra(tHashPalavras * hashPalavras, char* palavra, int documento);
void imprimeHash(tHashPalavras * hashPalavras, int documento);
void destroiHashPalavras(tHashPalavras * h);

#endif
