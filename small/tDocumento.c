#include "tDocumento.h"
#include "tPalavra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct documento {

  char nome[1024];
  int indiceNaLista;
  char classe[4];
  tPalavra ** palavras;
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

void Documento_destroi(tDocumento * d) {
  free(d->palavras);
  free(d->tf_idf);
  free(d->qtd_ocorrencias_palavras);

  free(d);

}

char *Documento_get_nome(tDocumento* d){ return d->nome; }
