#ifndef DOC_H
#define DOC_H
#include <stdio.h>
#include <stdlib.h>

typedef struct documento tDocumento;
typedef struct palavra dPalavra;
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
tDocumento* Documento_atribui_tf_idf(tDocumento* , int , int );
char *Documento_get_nome_palavra(tDocumento *, int );
char *Documento_get_classe(tDocumento* );
int Documento_Tem_palavra_documento(tDocumento * ,char * );
void Documento_imprime(tDocumento*, int);
#endif