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
  double tf_idf;
};

struct documento {

  char nome[100];
  int indiceNaLista;
  char classe[4];
  int qtd_palavras_dif_lidas;
  int qtd_palavras_total;
  int qtd_palavras_dif_alocadas;

  dPalavra **palavras;
};


tDocumento *Documento_constroi(char *nome, char *classe, int indice) {
  tDocumento *d = calloc(1, sizeof(tDocumento));
  d->palavras = calloc(100, sizeof(dPalavra*));
  
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
void Docf_inicializa(Docf **vet_soma_busca,int qtd){
  for(int i=0;i<qtd;i++){
    vet_soma_busca[i]=calloc(1,sizeof(Docf));
    vet_soma_busca[i]->idcDoc=0;
    vet_soma_busca[i]->tf_idf=0.0;
  }
}
void Documento_imprime_docf(Docf ** vet_soma_busca,int qtdDocs, tDocumento ** vetDocs){
  printf("Lista de documentos relacionados com a busca:\n\n");
  for(int i=qtdDocs-1;i>qtdDocs-11;i--){
    if(vet_soma_busca[i]->tf_idf==0.00){
      break;
    }
    int idc=vet_soma_busca[i]->idcDoc;
    printf("Documento %d: %s | TF-IDF[%lf] | Indice:%d\n",qtdDocs-i,Documento_get_nome(vetDocs[idc]),vet_soma_busca[i]->tf_idf,idc);
    //Documento_imprime_palavras(vetDocs[idc]);
    //printf("indice do documento: %d\n",vet_soma_busca[i].idcDoc);
  }
}
int Documento_get_indice(tDocumento *d){ return d->indiceNaLista;}
int Documento_compara(const void * d1, const void * d2){
  Docf * doc1=*((Docf**)d1);
  Docf * doc2=*((Docf**)d2);
  if(doc1->tf_idf > doc2->tf_idf){
    return 1;
  }else if(doc1->tf_idf < doc2->tf_idf){
    return -1;
  }
  return 0;
}
void Documento_soma_tfidf(Docf ** vet_soma_busca,int idcDoc,double tf_idf){
  //printf("valor antes da soma:%lf\n",tf_idf);
  vet_soma_busca[idcDoc]->tf_idf=tf_idf+vet_soma_busca[idcDoc]->tf_idf;
  //printf("valor depois da soma:%lf\n",vet_soma_busca[idcDoc]->tf_idf);
}
void Documento_atribui_idc(Docf * doc, int idc){
  doc->idcDoc=idc;
}
tDocumento *Documento_adiciona_palavra(tDocumento *d, char *nomeP) {

  int lidas=d->qtd_palavras_dif_lidas, alocadas=d->qtd_palavras_dif_alocadas, i=0;
  
  for (; i<lidas;i++){
    if (strcmp(nomeP, d->palavras[i]->palavra)==0){
      d->palavras[i]->qtd_ocorrencias_palavras++;
      return d;
    }
  }

  if (lidas>=alocadas){
    alocadas*=2;
    d->palavras=realloc(d->palavras, alocadas*sizeof(dPalavra*));
  }
  //printf("DOC '%s': LIDAS %d E ALOCADAS %d\n", d->nome, lidas, alocadas);

  d->qtd_palavras_total++;
  d->qtd_palavras_dif_alocadas=alocadas;
  d->qtd_palavras_dif_lidas++;
  d->palavras[i]=calloc(1,sizeof(dPalavra));
  strcpy(d->palavras[i]->palavra,nomeP);
  d->palavras[i]->qtd_ocorrencias_palavras=1;
  d->palavras[i]->tf_idf=0;

  return d;
}

void Documento_imprime_palavras(tDocumento *d){
  printf("qtd_palavras_dif_lidas: %d\n", d->qtd_palavras_dif_lidas);
  printf("Aparece no Documento: train%s %s com indice:%d qt:%d\n\n",d->nome,d->classe,d->indiceNaLista,d->qtd_palavras_dif_lidas);
  for (int i=0; i<d->qtd_palavras_dif_lidas; i++){
    printf("PALAVRA '%s': %d vezes TF-IDF: %lf\n", d->palavras[i]->palavra, d->palavras[i]->qtd_ocorrencias_palavras, d->palavras[i]->tf_idf);
  }
}

void Documento_destroi(tDocumento * d) {
  for(int i=0;i<d->qtd_palavras_dif_lidas;i++){
    free(d->palavras[i]);
  }
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


void Documento_escreve_bin(tDocumento * documento,FILE * file){
  
  int tam=strlen(documento->nome)+1;
  fwrite(&tam,sizeof(int),1,file);
  fwrite(documento->nome,sizeof(char),tam,file);
  fwrite(documento->classe,sizeof(char),4,file);
  fwrite(&documento->indiceNaLista,sizeof(int),1,file);
  fwrite(&documento->qtd_palavras_dif_lidas,sizeof(int),1,file);
  fwrite(&documento->qtd_palavras_total,sizeof(int),1,file);
  for(int i=0;i<documento->qtd_palavras_dif_lidas;i++){
    int size=strlen(documento->palavras[i]->palavra);
    fwrite(&size,sizeof(int),1,file);
    fwrite(documento->palavras[i]->palavra,sizeof(char),size,file);
    fwrite(&documento->palavras[i]->qtd_ocorrencias_palavras,sizeof(int),1,file);
    fwrite(&documento->palavras[i]->tf_idf,sizeof(double),1,file);
  }
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
  documento->palavras=calloc(documento->qtd_palavras_dif_lidas,sizeof(dPalavra*));
 for(int i=0;i<documento->qtd_palavras_dif_lidas;i++){
    int size;
    documento->palavras[i]=calloc(1,sizeof(dPalavra));
    fread(&size,sizeof(int),1,file);
    fread(documento->palavras[i]->palavra,sizeof(char),size,file);
    fread(&documento->palavras[i]->qtd_ocorrencias_palavras,sizeof(int),1,file);
    fread(&documento->palavras[i]->tf_idf,sizeof(double),1,file);
  }
  //Documento_imprime_palavras(documento);  
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

char *Documento_get_nome_palavra(tDocumento* d, int idc){ return d->palavras[idc]->palavra; }

int Documento_Tem_palavra_documento(tDocumento * documento,char * p){
    for(int i=0;i<Documento_get_qtd_palavras(documento);i++){
      if(strcmp(Documento_get_nome_palavra(documento,i),p)){
        return 1;
      }
    }
        
    return 0;
}

tDocumento* Documento_atribui_tf_idf(tDocumento* d, char* palavra, double tfidf){
  int i=0;
  for (; i<d->qtd_palavras_dif_lidas; i++){
    if (!strcmp(palavra, d->palavras[i]->palavra)){
      d->palavras[i]->tf_idf=tfidf;
      break;
    }
  }
  printf("Documento '%d', palavra: %s , tf-idf: %lf  \n", d->indiceNaLista, d->palavras[i]->palavra, d->palavras[i]->tf_idf);
  return d;
}

int Documento_get_ocorrencia_palavra(tDocumento *d, char * p){

  for (int i=0; i<d->qtd_palavras_dif_lidas; i++){
    if (!strcmp(p, d->palavras[i]->palavra)){
          return d->palavras[i]->qtd_ocorrencias_palavras;
    }
  }
return 0;
}

int Documento_get_indice_palavra(tDocumento*d, char*p){
  printf("1\n");
  for (int i=0; i<d->qtd_palavras_dif_lidas; i++){
    if (!strcmp(p, d->palavras[i]->palavra)){
      printf("2\n");
          return i;
    }
  }
  printf("3\n");
  return -1;
}

double Documento_calcula_mult_numerador(tDocumento*d1, tDocumento*d2, char*p){
  int i1=Documento_get_indice_palavra(d1, p), i2=Documento_get_indice_palavra(d2, p);

  if (i2==-1){
    return 0;
  }
  double idf1=d1->palavras[i1]->tf_idf, idf2=d2->palavras[i2]->tf_idf;

  return idf1* idf2;
}

double Documento_calcula_cosseno(tDocumento*d1, tDocumento *d2){
  double cos=0, numerador=0;
  char palavra[50];

  for (int i=0; i<d1->qtd_palavras_dif_lidas; i++){
      strcpy(palavra, Documento_get_nome_palavra(d1, i));
      printf("palavra: %s\n", palavra);
      numerador+=Documento_calcula_mult_numerador(d1, d2, palavra);
  }

  printf("NUMERADOR: %lf\n", numerador);
  return cos;

}