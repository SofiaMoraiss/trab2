#ifndef DOC_H
#define DOC_H
#include <stdio.h>
#include <stdlib.h>

typedef struct documento tDocumento;


tDocumento *Documento_constroi();
void Documento_destroi();
int Documento_get_indice(tDocumento *d);
char *Documento_get_nome(tDocumento* d);

#endif