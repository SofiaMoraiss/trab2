#ifndef DOC_H
#define DOC_H
#include <stdio.h>
#include <stdlib.h>

typedef struct documento tDocumento;


tDocumento *Documento_constroi();
int Documento_get_indice(tDocumento *d);

#endif