#include "tListas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tDocumento.h"
#include "tPalavra.h"

struct listas
{
  tDocumento **vetDocumentos;
  int qtd_docs_lidos;
  int qtd_palavras_lidas;
  int qtd_docs_alocados;
  tHashPalavras *hash;
};

tListas *Listas_adiciona_doc(tListas *l, tDocumento *doc)
{
  int qtd_lidas = l->qtd_docs_lidos;

  if (qtd_lidas >= l->qtd_docs_alocados)
  {
    l->vetDocumentos = realloc(l->vetDocumentos, (l->qtd_docs_alocados * 2) *
                                                     sizeof(tDocumento *));
    l->qtd_docs_alocados *= 2;
  }

  l->vetDocumentos[qtd_lidas] = doc;
  l->qtd_docs_lidos++;
  // printf("QTD DE DOCS LIDOS E ALOCADOS: %d %d\n", l->qtd_docs_lidos,
  // l->qtd_docs_alocados);
  return l;
}


tListas *Listas_constroi()
{
  tListas *l = calloc(1, sizeof(tListas));

  l->vetDocumentos = calloc(2, sizeof(tDocumento *));
  l->qtd_docs_alocados = 2;
  l->qtd_docs_lidos = 0;;
  l->hash = Hash_cria();
  return l;
}

void Listas_destroi(tListas *l)
{
  for (int i = 0; i < l->qtd_docs_lidos; i++)
  {
    Documento_destroi(l->vetDocumentos[i]);
  }
  free(l->vetDocumentos);

  Hash_destroi(l->hash);
  free(l);
}

tListas *Listas_ler_train(char *caminhoDocumentos, FILE *arqNomeDoc)
{
  tDocumento *doc;
  tListas *l = Listas_constroi();
  while (1)
  {
    char classe[4];
    char leitura[101];
    char path[1024];
    fscanf(arqNomeDoc, "train%s %[^\n]", leitura, classe);
    fscanf(arqNomeDoc, "%*c");
    sprintf(path, "%s%s", caminhoDocumentos, leitura);
    if (feof(arqNomeDoc))
    {
      break;
    }
    FILE *arqConteudoDoc = fopen(path, "r");
    if (!arqConteudoDoc)
    {
      printf("Erro! não foi possivel encontrar o arquivo");
      break;
    }
    doc = Documento_constroi(leitura, classe, l->qtd_docs_lidos);
    printf("\nVOU LER ARQUIVO : %s\n", path);
    printf("TIPO DA NOTICIA : %s\n", classe);
    // ao sair dessa funcao temos uma lista
    l = Listas_ler_noticia(arqConteudoDoc, l, doc);
    l = Listas_adiciona_doc(l, doc);
  }
  return l;
}

tListas *Listas_ler_noticia(FILE *arqDoc, tListas *l, tDocumento *d)
{
  // printf("NOME DENTRO DO LISTAS LER NOTICIAS: %s\n", Documento_get_nome(d));
  while (1)
  {
    char palavra[50];
    memset(palavra,'\0',sizeof(char));
    // printf("palavra\n");
    fscanf(arqDoc, "%s", palavra);
    if(feof(arqDoc)){
      break;
    }
    // printf("indice: %d\n", Documento_get_indice(d));
     Hash_adiciona_palavra(l->hash, palavra, Documento_get_indice(d));
  }
  printf("LI ARQ N '%d'\n", Documento_get_indice(d));
  fclose(arqDoc);
  return l;
}
tHashPalavras *Listas_get_hash(tListas *lista)
{
  return lista->hash;
}


void Listas_gera_binario(tListas * l, char * nomeBin){
 FILE*arqIndices=fopen(nomeBin,"wb");
 printf("%d esse aqui\n",l->qtd_palavras_lidas);
  for (int i = 0; i < Hash_get_idc_max(l->hash); i++)
  {
    if(i==0){
      fwrite(&(l->qtd_palavras_lidas),sizeof(int),1,arqIndices);
    }
    if (Hash_get_no_palavra(l->hash,i) != NULL)
    {
        tListaPalavra * temp=Hash_get_no_palavra(l->hash,i);
      while ( temp!= NULL)
      {
        fwrite(Hash_get_palavra(temp),Palavra_get_num_bytes(),1,arqIndices);
        temp=Hash_atribui_prox_no(temp);
      }
    }
  }
  fclose(arqIndices);
  arqIndices=fopen(nomeBin,"r");
  int qtd;
     
    fread(&qtd,sizeof(int),1,arqIndices);
    for(int i=0;i<qtd;i++){
      if(i==0){
        printf("%d oiiiiiiii\n",qtd);
      }
      tPalavra * palavra=calloc(1,Palavra_get_num_bytes());
      fread(palavra,Palavra_get_num_bytes(),1,arqIndices);
      Palavra_imprime(palavra);
      free(palavra);
    }
    fclose(arqIndices);
}

tListas * Listas_calcula_tf_idfs(tListas*l){

  tHashPalavras *hash= Listas_get_hash(l);
  for (int i = 0; i < Hash_get_idc_max(hash); i++)
  {
    if (Hash_get_no_palavra(hash,i) != NULL)
    {
      tListaPalavra * temp=Hash_get_no_palavra(hash,i);
      while ( temp!= NULL)
      {
        tPalavra* p= Hash_get_palavra(temp);
        p=Palavra_constroi_todos_TFIDFs(p, l->qtd_docs_lidos);
        temp=Hash_atribui_prox_no(temp);
      }
    }
  }
  return l;
}