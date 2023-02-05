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
int Docf_get_numBytes();
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
void Documento_escreve_bin(tDocumento * documento,FILE * file);
tDocumento ** Documento_le_indice(FILE * file,int * qtd);
tDocumento * Documento_le_bin(FILE * file);
void Documento_destroi_idc(tDocumento ** vetDocumentos,int qtdDocsLidos);
void Documento_soma_tfidf(Docf **vet_soma_busca,int idcDoc,double tf_idf);
int Documento_compara(const void *,const void*);
void Documento_imprime_docf(Docf **vet_soma_busca,int qtdDocs,tDocumento ** vetDoc);
void Documento_imprime(tDocumento *doc);
void Docf_inicializa(Docf **vet_soma_busca,int qtd);
void Documento_atribui_idc(Docf * doc, int idc);
#endif