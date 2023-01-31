#pragma once

typedef struct palavra tPalavra;

tPalavra *Palavra_constroi(char *);
void Palavra_destroi(tPalavra *);
char* get_nome(tPalavra* palavra);
int get_ocorrencia(tPalavra* palavra, int documento);
void Adiciona_ocorrencia(tPalavra * palavra, int documento);
void ImprimePalavra(tPalavra * p);
int ComparaPalavra(const void *ptr, const void *ptr2);
int Palavra_retornaNumBytes();
