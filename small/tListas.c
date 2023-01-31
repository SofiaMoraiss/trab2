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
  int qtd_docs_alocados;
  tPalavra **vetPalavras;
  int qtd_palavras_lidas;
  int qtd_palavras_alocadas;
  int teste;
  tHashPalavras *hash;
};

tListas *Lista_adiciona_doc(tListas *l, tDocumento *doc)
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

tListas *Lista_adiciona_palavra(tListas *l, tPalavra *p)
{
  int qtd_lidas = l->qtd_palavras_lidas;
  if (qtd_lidas >= l->qtd_palavras_alocadas)
  {
    l->vetPalavras = realloc(l->vetPalavras, (l->qtd_palavras_alocadas * 2) *
                                                 sizeof(tPalavra *));
    l->qtd_palavras_alocadas *= 2;
  }

  l->vetPalavras[qtd_lidas] = p;
  return l;
}

tListas *Lista_constroi()
{
  tListas *l = calloc(1, sizeof(tListas));

  l->vetDocumentos = calloc(2, sizeof(tDocumento *));
  l->qtd_docs_alocados = 2;
  l->qtd_docs_lidos = 0;
  l->vetPalavras = calloc(100, sizeof(tPalavra *));
  l->qtd_palavras_alocadas = 100;
  l->qtd_palavras_lidas = 0;
  l->teste=0;
  printf("construi lista antes do hash\n");
  l->hash = Hash_cria_palavras();
  return l;
}

void Lista_destroi(tListas *l)
{
  for (int i = 0; i < l->qtd_docs_lidos; i++)
  {
    Documento_destroi(l->vetDocumentos[i]);
  }
  free(l->vetDocumentos);
  for (int i = 0; i < l->qtd_palavras_lidas; i++)
  {
    Palavra_destroi(l->vetPalavras[i]);
  }
  free(l->vetPalavras);

  destroiHashPalavras(l->hash);
  free(l);
}

tListas *Listas_ler_train(char *caminhoDocumentos, FILE *arqNomeDoc)
{
  tDocumento *doc;
  tListas *l = Lista_constroi();
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
    l = Lista_adiciona_doc(l, doc);
  }
  l=Listas_atribui_vetor_palavras(l,l->hash);
  printf("%d-----\n",l->qtd_palavras_lidas);
  return l;
}
void Lista_ordena_vetor(tListas *l){
    qsort(l->vetPalavras,l->qtd_palavras_lidas,sizeof(tPalavra*),ComparaPalavra);
}
tListas* Listas_atribui_vetor_palavras(tListas *l, tHashPalavras *hash)
{
  for (int i = 0; i < Obtem_idc_max(hash); i++)
  {
    
    if (ObtemNoPalavra(hash,i) != NULL)
    {
        tListaPalavra * temp=ObtemNoPalavra(hash,i);
      while ( temp!= NULL)
      {
        //ImprimePalavra(Obtem_palavra(temp));
        //printf("%d-----\n",l->teste);
        l=Lista_adiciona_palavra(l,Obtem_palavra(temp));
        l->vetPalavras[l->qtd_palavras_lidas]=Obtem_palavra(temp);
        l->qtd_palavras_lidas++;
        //printf("\nQTD DE PALAVRAS LIDAS E ALOCADAS: %d %d\n", l->qtd_palavras_lidas,
        //l->qtd_palavras_alocadas);
        temp=AtribuiProxNo(temp);
      }
    }
  }
  return l;
}
void Lista_imprime_vet_palavras(tListas *l){
  
  for(int i=0;i<l->qtd_palavras_lidas;i++){
    ImprimePalavra(l->vetPalavras[i]);
  }
  printf("====%d\n",l->qtd_palavras_lidas);
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
tHashPalavras *Lista_get_hash(tListas *lista)
{
  return lista->hash;
}
void GeraBinario(tListas * l, char * nomeBin){
 FILE*arqIndices=fopen(nomeBin,"wb");
 printf("%d esse aqui\n",l->qtd_palavras_lidas);
  for (int i = 0; i < Obtem_idc_max(l->hash); i++)
  {
    if(i==0){
      fwrite(&(l->qtd_palavras_lidas),sizeof(int),1,arqIndices);
    }
    if (ObtemNoPalavra(l->hash,i) != NULL)
    {
        tListaPalavra * temp=ObtemNoPalavra(l->hash,i);
      while ( temp!= NULL)
      {
        fwrite(Obtem_palavra(temp),Palavra_retornaNumBytes(),1,arqIndices);
        temp=AtribuiProxNo(temp);
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
      tPalavra * palavra=calloc(1,Palavra_retornaNumBytes());
      fread(palavra,Palavra_retornaNumBytes(),1,arqIndices);
      ImprimePalavra(palavra);
      free(palavra);
    }
    fclose(arqIndices);
}
