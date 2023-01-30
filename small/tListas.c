#include "tListas.h"
#include "tDocumento.h"
#include "tPalavra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listas {

  tDocumento **vetDocumentos;
  int qtd_docs_lidos;
  int qtd_docs_alocados;
  tPalavra **vetPalavras;
  int qtd_palavras_lidas;
  int qtd_palavras_alocadas;

  tHashPalavras *hash;
};

tListas *Lista_adiciona_doc(tListas *l, tDocumento *doc) {
  int qtd_lidas = l->qtd_docs_lidos;

  if (qtd_lidas >= l->qtd_docs_alocados) {
    l->vetDocumentos = realloc(l->vetDocumentos, (l->qtd_docs_alocados * 2) *
                                                     sizeof(tDocumento *));
    l->qtd_docs_alocados *= 2;
  }

  l->vetDocumentos[qtd_lidas] = doc;
  l->qtd_docs_lidos++;
  printf("QTD DE DOCS LIDOS E ALOCADOS: %d %d", l->qtd_docs_lidos,
         l->qtd_docs_alocados);
  return l;
}

tListas *Lista_adiciona_palavra(tListas *l, tPalavra *p)
{
    int qtd_lidas= l->qtd_palavras_lidas;
      if (qtd_lidas >= l->qtd_palavras_alocadas) {
    l->vetPalavras = realloc(l->vetPalavras, (l->qtd_palavras_alocadas * 2) *
                                                     sizeof(tPalavra *));
    l->qtd_palavras_alocadas*= 2;
  }

  l->vetPalavras[qtd_lidas] = p;
  l->qtd_palavras_lidas++;
  printf("\nQTD DE PALAVRAS LIDAS E ALOCADAS: %d %d\n", l->qtd_palavras_lidas,
         l->qtd_palavras_alocadas);
  return l;
}

tListas *Lista_constroi() {
  tListas *l = calloc(1, sizeof(tListas));

  l->vetDocumentos = calloc(2, sizeof(tDocumento *));
  l->qtd_docs_alocados = 2;
  l->qtd_docs_lidos = 0;
  l->vetPalavras = calloc(100, sizeof(tPalavra *));
  l->qtd_palavras_alocadas = 100;
  l->qtd_palavras_lidas = 0;
  printf("construi lista antes do hash\n");
  l->hash = criaHashPalavras();
  return l;
}

void Lista_destroi(tListas* l) {
  tListas *l = calloc(1, sizeof(tListas));

  l->vetDocumentos = calloc(2, sizeof(tDocumento *));
  l->qtd_docs_alocados = 2;
  l->qtd_docs_lidos = 0;
  l->vetPalavras = calloc(100, sizeof(tPalavra *));
  l->qtd_palavras_alocadas = 100;
  l->qtd_palavras_lidas = 0;

  l->hash = criaHashPalavras();
  return l;
}

tListas * Listas_ler_train(FILE *arqTrain) {
  char line[1000], nome[100], classe[4];
  tDocumento *doc;
  tListas *l = Lista_constroi();
  while (!feof(arqTrain)) {
    fscanf(arqTrain, "\n\r%[^\n]\n\r", line);
    printf("%s\n", line);

    char *token = strtok(line, " ");
    strcpy(nome, token);
    printf("NOME: %s\n", nome);
    token = strtok(NULL, " ");
    strcpy(classe, token);
      
    doc = Documento_constroi(nome, classe, l->qtd_docs_lidos);
    printf("\nVOU LER ARQUIVO : %s\n", nome);
    printf("\nTIPO DA NOTICIA : %s\n", classe);

    FILE *arqDoc = fopen(nome, "r");
    if (arqDoc == NULL) {
      printf("Não achei arquivo %s", nome);
    }
    l=Listas_ler_noticia(arqDoc, l, doc);
    l=Lista_adiciona_doc(l, doc);

  }
  return l;
}

tListas *Listas_ler_noticia(FILE *arqDoc, tListas *l, tDocumento *d) {
  char palavra[50];
  while (!feof(arqDoc)) {
    fscanf(arqDoc, "%s", palavra);
    adicionaPalavra(l->hash, palavra, Documento_get_indice(d));
    //p= Palavra_constroi(palavra);
    //l= Lista_adiciona_palavra(l, p);
    // d->palavras[]
    //printf("/ %s", palavra);
  }
  if (Documento_get_indice(d)==0 || Documento_get_indice(d)==1){
    imprimeHash(l->hash, Documento_get_indice(d));
  }
  return l;
}