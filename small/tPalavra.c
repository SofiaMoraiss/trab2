#include "tPalavra.h"
#include "tHashPalavras.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct palavra {
    char nome[100];
    int qtd_documentos_alocados;
    int qtd_documentos_q_apareceu;
    int * vetDocumentos;
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
    d->vetDocumentos = calloc(100, sizeof(int));

    d->qtd_documentos_alocados = 100;
    d->qtd_documentos_q_apareceu=0;
    return d;
}

void Palavra_destroi(tPalavra *palavra) {
    free(palavra->qtd_ocorrencias);
    free(palavra->tf_idf);
    free(palavra->vetDocumentos);
    free(palavra);
}

char *Palavra_get_nome(tPalavra *palavra) {
    return palavra->nome;
}

int Palavra_get_ocorrencia(tPalavra *palavra, int documento) {
    if (documento > palavra->qtd_documentos_alocados)
        return 0;
    return palavra->qtd_ocorrencias[documento];
}

int Palavra_get_ocorrencia2(tPalavra *p, int doc) {

    for (int i=0; i<p->qtd_documentos_q_apareceu; i++){
        if (p->vetDocumentos[i]==doc){
            return p->qtd_ocorrencias[i];
        }
    }
    return 0;
}

void Palavra_adiciona_ocorrencia(tPalavra *palavra, int documento) {
    while (documento >= palavra->qtd_documentos_alocados) {
        palavra->qtd_documentos_alocados += 1;
        palavra->qtd_ocorrencias = realloc(palavra->qtd_ocorrencias, palavra->qtd_documentos_alocados * sizeof(int));
        palavra->tf_idf = realloc(palavra->tf_idf, palavra->qtd_documentos_alocados * sizeof(int));
        for (int i = documento; i < palavra->qtd_documentos_alocados; i++) {
            palavra->qtd_ocorrencias[i] = 0;
            palavra->tf_idf[i] = 0;
        }
    }
    palavra->qtd_ocorrencias[documento] += 1;
}

void Palavra_adiciona_ocorrencia2(tPalavra *p, int doc) {
    if (p->qtd_documentos_q_apareceu >= p->qtd_documentos_alocados) 
    {
        p->qtd_documentos_alocados *= 2;

        p->tf_idf = realloc(p->vetDocumentos, p->qtd_documentos_alocados * sizeof(int));
        p->qtd_ocorrencias = realloc(p->qtd_ocorrencias, p->qtd_documentos_alocados * sizeof(int));
        p->tf_idf = realloc(p->tf_idf, p->qtd_documentos_alocados * sizeof(int));
        for (int i = p->qtd_documentos_q_apareceu; i < p->qtd_documentos_alocados; i++) {
            p->qtd_ocorrencias[i] = 0;
            p->tf_idf[i] = 0;
        }
    }
    int idc=p->qtd_documentos_q_apareceu;
    p->vetDocumentos[idc]=doc;
    p->qtd_ocorrencias[idc] += 1;
    p->qtd_documentos_q_apareceu++;
}

void Palavra_imprime(tPalavra * p){
  printf("%s\n",p->nome);
}
int Palavra_get_num_bytes(){
    return sizeof(tPalavra);
}

double Palavra_calcula_tf_idf(tPalavra *p, int doc, int nTotaldeDocs)
{
    int qtd_documentos_que_aparece = 0;

    for (int i = 0; i < p->qtd_documentos_alocados; i++)
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