#ifndef LISTAS_H
#define LISTAS_H

#include <stdlib.h>

#include "tDocumento.h"
#include "tHashPalavras.h"
#include "tPalavra.h"

typedef struct listas tListas;

tListas *Listas_adiciona_doc(tListas *, tDocumento *);
tListas *Listas_constroi();
tListas *Listas_adiciona_palavra(tListas *, tPalavra *);
tListas *Listas_ler_noticia(FILE *, tListas *, tDocumento *);
void Listas_destroi(tListas *);
tListas *Listas_ler_train(char *, FILE *);
tHashPalavras *Listas_get_hash(tListas *);
tListas * Listas_atribui_vetor_palavras(tListas *l, tHashPalavras *hash);
void Listas_imprime_vet_palavras(tListas *l);
void Listas_ordena_vetor(tListas *l);
void Listas_gera_binario(tListas * l, char * caminho);

#endif