#include "tDocumento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct documento {

  char nome[100];
  int indiceNaLista;
  char classe[4];
  int *palavras;
  int *qtd_ocorrencias_palavras;
  float *tf_idf;
};

tDocumento *Documento_constroi(char *nome, char *classe, int indice) {
  tDocumento *d = calloc(1, sizeof(tDocumento));
  d->palavras = calloc(100, sizeof(int));
  d->qtd_ocorrencias_palavras = calloc(100, sizeof(int));
  d->tf_idf = calloc(100, sizeof(int));

  strcpy(d->classe, classe);
  strcpy(d->nome, nome);
  d->indiceNaLista=indice;

  return d;
}

int Documento_get_indice(tDocumento *d){ return d->indiceNaLista;}


