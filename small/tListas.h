#ifndef LISTAS_H
#define LISTAS_H

#include <stdlib.h>

#include "tDocumento.h"
#include "tHashPalavras.h"
#include "tPalavra.h"

typedef struct listas tListas;

tListas *Lista_adiciona_doc(tListas *, tDocumento *);
tListas *Lista_constroi();
tListas *Lista_adiciona_palavra(tListas *, tPalavra *);
tListas *Listas_ler_noticia(FILE *, tListas *, tDocumento *);
void Lista_destroi(tListas *);
tListas *Listas_ler_train(char *, FILE *);
tHashPalavras *Lista_get_hash(tListas *);
tListas * AtribuiVetorPalavras(tListas *l, tHashPalavras *hash);
void ImprimeVetPalavras(tListas *l);

#endif