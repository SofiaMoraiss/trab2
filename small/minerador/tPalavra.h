#ifndef PALAVRA_H
#define PALAVRA_H
#include <stdio.h>

typedef struct palavra tPalavra;
typedef struct vetdoc tVetDocumentos;

tPalavra *Palavra_constroi(char *);
void Palavra_destroi(tPalavra *);
char *Palavra_get_nome(tPalavra *);
double Palavra_get_tf_idf(tPalavra *, int);
int Palavra_get_ocorrencia(tPalavra *, int);
int Palavra_get_qtd_docs_q_aparece(tPalavra *);
int Palavra_get_idc_doc(tPalavra *,int );
void Palavra_imprime_idfs(tPalavra * );
void Palavra_adiciona_ocorrencia(tPalavra *, int);
void Palavra_imprime(tPalavra *);
int Palavra_compara(const void *, const void *);
int Palavra_get_num_bytes();
//recebe palavra e o indice no p->vetDoc e retorna o indice do doc
void Palavra_imprime_idfs(tPalavra * );
int Palavra_get_idc_doc(tPalavra *, int );
tPalavra *Palavra_constroi_todos_TFIDFs(tPalavra *, int);
double Palavra_calcula_1tf_idf(int, int, int);
double *Palavra_get_vetTFIDF(tPalavra *);
tPalavra * Palavra_costrutor();
void Palavra_escreve_binario(tPalavra * , FILE * );
tPalavra * Palavra_le_binario(FILE  * );
int Palavra_get_tam(tPalavra *);
#endif