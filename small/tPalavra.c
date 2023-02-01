#include "tPalavra.h"
#include "tHashPalavras.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct palavra {
    char nome[100];
    int qtd_documentosAlocados;
    //frequencia de uma palavra em cada documento
    int *qtd_ocorrencias;
    float *tf_idf;
};

int Palavra_compara(const void *ptr, const void *ptr2) {
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

char *Palavra_get_nome(tPalavra *palavra) {
    return palavra->nome;
}

int Palavra_get_ocorrencia(tPalavra *palavra, int documento) {
    if (documento > palavra->qtd_documentosAlocados)
        return 0;
    return palavra->qtd_ocorrencias[documento];
}

void Palavra_adiciona_ocorrencia(tPalavra *palavra, int documento) {
    while (documento >= palavra->qtd_documentosAlocados) {
        palavra->qtd_documentosAlocados += 1;
        palavra->qtd_ocorrencias = realloc(palavra->qtd_ocorrencias, palavra->qtd_documentosAlocados * sizeof(int));
        palavra->tf_idf = realloc(palavra->tf_idf, palavra->qtd_documentosAlocados * sizeof(int));
        for (int i = documento; i < palavra->qtd_documentosAlocados; i++) {
            palavra->qtd_ocorrencias[i] = 0;
            palavra->tf_idf[i] = 0;
        }
    }
    //printf("%d\n",palavra->qtd_ocorrencias[documento]);
    palavra->qtd_ocorrencias[documento] += 1;
}
void Palavra_imprime(tPalavra * p){
  printf("%s\n",p->nome);
}
int Palavra_get_num_bytes(){
    return sizeof(tPalavra);
}

double Palavra_calcula_tf_df(tPalavra *p, int doc, int nTotaldeDocs)
{
    int qtd_documentos_que_aparece = 0;

    for (int i = 0; i < p->qtd_documentosAlocados; i++)
    {
        if (1/*p->qtd_ocorrencias[i]!=NULL*/){
            if (Palavra_get_ocorrencia(p, i) > 0){
                qtd_documentos_que_aparece++;
            }
        }
    }

    int df = qtd_documentos_que_aparece;
    int n = nTotaldeDocs;
    int tf = Palavra_get_ocorrencia(p, doc);
    double TFIDF = 0;

    double idf = log((1 + n) / (1 + df));

    TFIDF = tf*idf;

    return TFIDF;
}