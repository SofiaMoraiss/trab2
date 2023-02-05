#ifndef DOC_H
#define DOC_H
#include <stdio.h>
#include <stdlib.h>

typedef struct palavra dPalavra;
typedef struct documento tDocumento;
typedef struct docTf_idf Docf;
tDocumento *Documento_constroi();
int Documento_get_numBytes();
void Documento_destroi();
int Documento_get_indice(tDocumento *);
char *Documento_get_nome(tDocumento *);
char *Documento_get_nome_palavra(tDocumento* , int );
int Documento_get_qtd_palavras(tDocumento* );
int Documento_get_qtd_palavras(tDocumento* );
tDocumento *Documento_adiciona_palavra(tDocumento *, char *);
void Documento_imprime_palavras(tDocumento *);
tDocumento * Documento_atribui_tf_idf(tDocumento* , char *, double );
char *Documento_get_nome_palavra(tDocumento *, int );
char *Documento_get_classe(tDocumento* );
int Documento_get_qtd_palavras_total(tDocumento* );
int Documento_Tem_palavra_documento(tDocumento * ,char * );
void Documento_escreve_bin(tDocumento * ,FILE * );
tDocumento ** Documento_le_indice(FILE * ,int * );
tDocumento * Documento_le_bin(FILE * );
void Documento_destroi_idc(tDocumento ** ,int );
void Documento_soma_tfidf(Docf **,int ,double );
int Documento_compara(const void *,const void*);
int Docf_get_numBytes();
double Documento_calcula_mult_numerador(tDocumento*, tDocumento*, char*);
double Documento_calcula_cosseno(tDocumento*, tDocumento *);
int Documento_get_ocorrencia_palavra(tDocumento *, char * );
//imprime um vetor do struct auxiliar de documentos;
void Documento_imprime_docf(Docf **,int ,tDocumento ** );
void Documento_imprime(tDocumento *);
void Docf_inicializa(Docf **,int );
void Documento_atribui_idc(Docf * , int );
#endif