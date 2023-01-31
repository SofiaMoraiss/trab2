#pragma once

typedef struct palavra tPalavra;

tPalavra *Palavra_constroi(char *);
void Palavra_destroi(tPalavra *);
char* Palavra_get_nome(tPalavra* palavra);
int Palavra_get_ocorrencia(tPalavra* palavra, int documento);
void Palavra_adiciona_ocorrencia(tPalavra * palavra, int documento);
void Palavra_imprime(tPalavra * p);
int Palavra_compara(const void *ptr, const void *ptr2);
int Palavra_get_num_bytes();
