#ifndef PALAVRA_H
#define PALAVRA_H

typedef struct palavra tPalavra;
typedef struct vetdoc tVetDocumentos;

tPalavra *Palavra_constroi(char *);
void Palavra_destroi(tPalavra *);
char* Palavra_get_nome(tPalavra* );
int Palavra_get_ocorrencia(tPalavra* , int );
void Palavra_adiciona_ocorrencia(tPalavra * , int );
void Palavra_adiciona_ocorrencia2(tPalavra *, int );
void Palavra_imprime(tPalavra * );
int Palavra_compara(const void *, const void *);
int Palavra_get_num_bytes();
double Palavra_calcula_tf_df(tPalavra *, int, int);

#endif