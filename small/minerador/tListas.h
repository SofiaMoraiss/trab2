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
tListas *Listas_ler_noticia(FILE *, tListas *, tDocumento *);
void Listas_destroi(tListas *);
void Listas_imprime_relatorio_palavra(char *, tListas *);
tListas *Listas_ler_train(char *, FILE *);
tHashPalavras *Listas_get_hash(tListas *);
tListas *Listas_atribui_vetor_palavras(tListas *, tHashPalavras *);
void Listas_imprime_vet_palavras(tListas *);
void Listas_ordena_vetor(tListas *);
void Listas_gera_binario(tListas *, char *);
tListas *Listas_calcula_tf_idfs(tListas * );
void Listas_busca_noticia(tHashPalavras * ,int );
void Listas_imprime_relatorio_documentos(tListas *);
