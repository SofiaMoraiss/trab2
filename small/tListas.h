#ifndef LISTAS_H
#define LISTAS_H

#include "tDocumento.h"
#include "tPalavra.h"
#include "tHashPalavras.h"
#include <stdlib.h>

typedef struct listas tListas;

tListas *Lista_adiciona_doc(tListas *, tDocumento *);
tListas *Lista_constroi();
tListas *Lista_adiciona_palavra(tListas *, tPalavra *);
tListas *Listas_ler_noticia(FILE *, tListas*, tDocumento *);
void Lista_destroi(tListas*);
tListas * Listas_ler_train(FILE *);

#endif