#ifndef PALAVRA_H
#define PALAVRA_H

typedef struct palavra tPalavra;
typedef struct vetdoc tVetDocumentos;

tPalavra *Palavra_constroi(char *);
void Palavra_destroi(tPalavra *);
char* Palavra_get_nome(tPalavra* );
double Palavra_get_tf_idf(tPalavra *, int);
int Palavra_get_ocorrencia(tPalavra* , int );
void Palavra_adiciona_ocorrencia(tPalavra * , int );
void Palavra_imprime(tPalavra * );
int Palavra_compara(const void *, const void *);
int Palavra_get_num_bytes();
tPalavra * Palavra_constroi_todos_TFIDFs(tPalavra *, int);
double Palavra_calcula_1tf_idf(int, int, int );
double * Palavra_get_vetTFIDF(tPalavra * p);

#endif