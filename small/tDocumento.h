#ifndef DOC_H
#define DOC_H
#include <stdio.h>
#include <stdlib.h>

typedef struct documento tDocumento;


tDocumento *Documento_constroi();
void Documento_destroi();
int Documento_get_indice(tDocumento *);
char *Documento_get_nome(tDocumento *);
tDocumento *Documento_adiciona_palavra(tDocumento *, char *);
void Documento_imprime_palavras(tDocumento *);

#endif