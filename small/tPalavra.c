#include "tPalavra.h"
#include "tHashPalavras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct palavra {
    char nome[100];
    int qtd_documentosAlocados;
    //frequencia de uma palavra em cada documento
    int *qtd_ocorrencias;
    float *tf_idf;
};

int ComparaPalavra(const void *ptr, const void *ptr2) {
    tPalavra *p1;
    tPalavra *p2;
    p1=*(tPalavra**)ptr;
    p2=*(tPalavra**)ptr2;
  return strcmp(p1->nome, p2->nome);
}
tPalavra *Palavra_constroi(char *nome) {
    tPalavra *d = calloc(1, sizeof(tPalavra));
    strcpy(d->nome, nome);
    d->qtd_ocorrencias = calloc(100, sizeof(int));
    d->tf_idf = calloc(100, sizeof(int));
    d->qtd_documentosAlocados = 100;
    return d;
}

void Palavra_destroi(tPalavra *palavra) {
    free(palavra->qtd_ocorrencias);
    free(palavra->tf_idf);
    free(palavra);
}

char *get_nome(tPalavra *palavra) {
    return palavra->nome;
}

int get_ocorrencia(tPalavra *palavra, int documento) {
    if (documento > palavra->qtd_documentosAlocados)
        return 0;
    return palavra->qtd_ocorrencias[documento];
}

void Adiciona_ocorrencia(tPalavra *palavra, int documento) {
    while (documento >= palavra->qtd_documentosAlocados) {
        palavra->qtd_documentosAlocados *= 2;
        palavra->qtd_ocorrencias = realloc(palavra->qtd_ocorrencias, palavra->qtd_documentosAlocados * sizeof(int));
        palavra->tf_idf = realloc(palavra->tf_idf, palavra->qtd_documentosAlocados * sizeof(int));
        for (int i = documento; i < palavra->qtd_documentosAlocados; i++) {
            palavra->qtd_ocorrencias[i] = 0;
            palavra->tf_idf[i] = 0;
        }
    }
    printf("%d\n",palavra->qtd_ocorrencias[documento]);
    palavra->qtd_ocorrencias[documento] += 1;
}
void ImprimePalavra(tPalavra * p){
  printf("%s\n",p->nome);
}