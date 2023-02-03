#include "tDocumento.h"
#include "tPalavra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct palavra {
  char palavra[50];
  int qtd_ocorrencias_palavras;
  double tf_idf;
} dPalavra;

struct docTf_idf{
  int idcDoc;
  double tfidfBsucas;
};

struct documento {

  char nome[100];
  int indiceNaLista;
  char classe[4];
  int qtd_palavras_dif_lidas;
  int qtd_palavras_total;
  int qtd_palavras_dif_alocadas;
  //tPalavra ** vetPalavras;

  struct palavra * palavras;
};


tDocumento *Documento_constroi(char *nome, char *classe, int indice) {
  tDocumento *d = calloc(1, sizeof(tDocumento));
  d->palavras = calloc(100, sizeof(dPalavra));
  
  /*for (int i=0; i<100; i++){
    d->palavras[i].qtd_ocorrencias_palavras=0;
    d->palavras[i].tf_idf=0;
  }*/

  strcpy(d->classe, classe);
  strcpy(d->nome, nome);
  d->indiceNaLista=indice;
  d->qtd_palavras_dif_lidas=0;
  d->qtd_palavras_dif_alocadas=100;

  return d;
}

int Documento_get_indice(tDocumento *d){ return d->indiceNaLista;}

/*int Documento_get_ocorrencias_palavra(tDocumento *d, tPalavra*p)
{ 
  return d->vetPalavras;
}*/

tDocumento *Documento_adiciona_palavra(tDocumento *d, char *nomeP) {

  int lidas=d->qtd_palavras_dif_lidas, alocadas=d->qtd_palavras_dif_alocadas, i=0;
  
  for (; i<lidas;i++){
    if (strcmp(nomeP, d->palavras[i].palavra)==0){
      d->palavras[i].qtd_ocorrencias_palavras++;
      return d;
    }
  }

  if (lidas>=alocadas){
    alocadas*=2;
    d->palavras=realloc(d->palavras, alocadas*sizeof(dPalavra));
    /*for (int i=lidas; i<alocadas; i++){
      d->palavras[i].qtd_ocorrencias_palavras=0;
      d->palavras[i].tf_idf=0;
    }*/
  }

  d->qtd_palavras_total++;
  d->qtd_palavras_dif_alocadas=alocadas;
  d->qtd_palavras_dif_lidas++;
  strcpy(d->palavras[i].palavra,nomeP);
  d->palavras[i].qtd_ocorrencias_palavras=1;
  d->palavras[i].tf_idf=0;

  return d;
}

void Documento_imprime_palavras(tDocumento *d){

  printf("qtd_palavras_dif_lidas: %d\n", d->qtd_palavras_dif_lidas);
  for (int i=0; i<d->qtd_palavras_dif_lidas; i++){
    printf("PALAVRA '%s': %d vezes TF-IDF: %lf\n", d->palavras[i].palavra, d->palavras[i].qtd_ocorrencias_palavras, d->palavras[i].tf_idf);
  }
}

void Documento_destroi(tDocumento * d) {
  free(d->palavras);
  free(d);
}

char *Documento_get_nome(tDocumento* d){ return d->nome; }

char *Documento_get_classe(tDocumento* d){ return d->classe; }

int Documento_get_qtd_palavras(tDocumento* d){ return d->qtd_palavras_dif_lidas; }

int Documento_get_qtd_palavras_total(tDocumento* d){ return d->qtd_palavras_total; }

int Documento_get_numBytes(){
  return sizeof(Docf);
}

char *Documento_get_nome_palavra(tDocumento* d, int idc){ return d->palavras[idc].palavra; }

int Documento_Tem_palavra_documento(tDocumento * documento,char * p){
    for(int i=0;i<Documento_get_qtd_palavras(documento);i++){
      if(strcmp(Documento_get_nome_palavra(documento,i),p)){
        return 1;
      }
    }
        
    return 0;
}

tDocumento * Documento_atribui_tf_idf(tDocumento* d, int idc, int tfidf){
  d->palavras[idc].tf_idf=tfidf;
  return d;
}

void Documento_imprime(tDocumento*d, int i){
  
  printf("%d: %s / %d palavras / Classe: %s\n", d->nome, i+1, d->qtd_palavras_total, d->classe);

}