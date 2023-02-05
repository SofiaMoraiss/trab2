#pragma once

#include <stdlib.h>

#include "tDocumento.h"
#include "tHashPalavras.h"
#include "tPalavra.h"

typedef struct listas tListas;
typedef struct noAux tNoAux;

tListas *Listas_adiciona_doc(tListas *, tDocumento *);
tListas *Listas_constroi();
tListas *Listas_adiciona_palavra(tListas *, tPalavra *);
//Le arquivo que contem a noticia
tListas *Listas_ler_noticia(FILE *, tListas *, tDocumento *);
void Listas_destroi(tListas *);
void Listas_imprime_relatorio_palavra(tHashPalavras *);
//Le arquivo que contem o nome dos documentos
tListas *Listas_ler_train(char *, FILE *);
tHashPalavras *Listas_get_hash(tListas *);
tListas *Listas_atribui_vetor_palavras(tListas *, tHashPalavras *);
void Listas_imprime_vet_palavras(tHashPalavras *);
void Listas_gera_binario(tListas *, char *);
tListas *Listas_calcula_tf_idfs(tListas * );
void Listas_busca_noticia(tHashPalavras * , int, tDocumento ** );
void Listas_imprime_relatorio_documentos(tHashPalavras *,tDocumento ** , int);
void Listas_imprime_saida(tListas * l);
