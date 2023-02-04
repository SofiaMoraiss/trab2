#include "tDocumento.h"
#include "tPalavra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct palavra {
  char palavra[50];
  int qtd_ocorrencias_palavras;
  double tf_idf;
};

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

  dPalavra * palavras;
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
int Docf_get_numBytes(){
  return sizeof(Docf);
}
void Documento_imprime_docf(Docf * vet_soma_busca,int qtdDocs, tDocumento ** vetDocs){
  for(int i=qtdDocs-1;i>qtdDocs-10;i--){
    int idc=vet_soma_busca[i].idcDoc;
    Documento_imprime_palavras(vetDocs[idc]);
    printf("tf_idf: %lf\n",vet_soma_busca[i].tfidfBsucas);
    //printf("indice do documento: %d\n",vet_soma_busca[i].idcDoc);
  }
}
void Documento_imprime(tDocumento *doc){

}
int Documento_get_indice(tDocumento *d){ return d->indiceNaLista;}
int Documento_compara(const void * d1, const void * d2){
  Docf * doc1=(Docf*)d1;
  Docf * doc2=(Docf*)d2;
  if(doc1->tfidfBsucas > doc2->tfidfBsucas){
    return 1;
  }else if(doc1->tfidfBsucas < doc2->tfidfBsucas){
    return -1;
  }
  return 0;
}
Docf * Documento_soma_tfidf(Docf * vet_soma_busca,int idcDoc,double tf_idf){
  vet_soma_busca[idcDoc].idcDoc=idcDoc;
  vet_soma_busca[idcDoc].tfidfBsucas+=tf_idf;
  //vet_soma_busca[idcDoc]->tfidfBsucas+=tf_idf;
  return vet_soma_busca;
}

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
  printf("%s %s %d %d\n",d->nome,d->classe,d->indiceNaLista,d->qtd_palavras_dif_lidas);
  // for (int i=0; i<d->qtd_palavras_dif_lidas; i++){
  //   //printf("PALAVRA '%s': %d vezes TF-IDF: %lf\n", d->palavras[i].palavra, d->palavras[i].qtd_ocorrencias_palavras, d->palavras[i].tf_idf);
  // }
}

void Documento_destroi(tDocumento * d) {
  free(d->palavras);
  free(d);
}
void   Documento_destroi_idc(tDocumento ** vetDocumentos,int qtdDocsLidos){
  for(int i=0;i<qtdDocsLidos;i++){
    Documento_destroi(vetDocumentos[i]);
  }
  free(vetDocumentos);
}


char *Documento_get_nome(tDocumento* d){ return d->nome; }

char *Documento_get_classe(tDocumento* d){ return d->classe; }

int Documento_get_qtd_palavras(tDocumento* d){ return d->qtd_palavras_dif_lidas; }

int Documento_get_qtd_palavras_total(tDocumento* d){ return d->qtd_palavras_total; }

int Documento_get_numBytes(){
  return sizeof(Docf);
}

void Documento_escreve_bin(tDocumento * documento,FILE * file){
  
  int tam=strlen(documento->nome)+1;
  fwrite(&tam,sizeof(int),1,file);
  fwrite(documento->nome,sizeof(char),tam,file);
  fwrite(documento->classe,sizeof(char),4,file);
  fwrite(&documento->indiceNaLista,sizeof(int),1,file);
  fwrite(&documento->qtd_palavras_dif_lidas,sizeof(int),1,file);
  fwrite(&documento->qtd_palavras_total,sizeof(int),1,file);
  //fwrite(documento->palavras,sizeof(dPalavra),documento->qtd_palavras_dif_lidas,file);
}
tDocumento * Documento_le_bin(FILE * file){
  tDocumento * documento=calloc(1,sizeof(tDocumento));
  int tam;
  fread(&tam,sizeof(int),1,file);

  fread(documento->nome,sizeof(char),tam,file);
  fread(documento->classe,sizeof(char),4,file);
  fread(&documento->indiceNaLista,sizeof(int),1,file);
  fread(&documento->qtd_palavras_dif_lidas,sizeof(int),1,file);
  fread(&documento->qtd_palavras_total,sizeof(int),1,file);
  //fread(documento->palavras,sizeof(dPalavra),documento->qtd_palavras_dif_lidas,file);
  return documento;
}
tDocumento ** Documento_le_indice(FILE * file,int * qtd){
      fread(qtd,sizeof(int),1,file);
      tDocumento ** vetDocumentos=calloc(*(qtd),sizeof(tDocumento*));     
      for(int i=0;i<*(qtd);i++){
        vetDocumentos[i]=Documento_le_bin(file);
      }
      return vetDocumentos;
      
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
