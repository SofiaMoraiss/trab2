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
  tDocsAux *vetDocsAux;
  tPalavrasAux *vetPalavrasAux;
};

struct docsAux {
  int idc;
  int qtd_palavras;
};

struct palavrasAux {
  int Idc;
  int qtd_palavras;
};

tListas *Listas_adiciona_doc(tListas *l, tDocumento *doc)
{
  int qtd_lidos = l->qtd_docs_lidos;

  if (qtd_lidos >= l->qtd_docs_alocados)
  {
    l->qtd_docs_alocados *= 2;
    l->vetDocumentos = realloc(l->vetDocumentos, (l->qtd_docs_alocados) *
                                                     sizeof(tDocumento *));
  }

  l->vetDocumentos[qtd_lidos] = doc;
  l->qtd_docs_lidos++;
  printf("QTD DE DOCS LIDOS E ALOCADOS: %d %d\n", l->qtd_docs_lidos, l->qtd_docs_alocados);
  // l->qtd_docs_alocados);
  return l;
}

tListas *Listas_constroi()
{
  tListas *l = calloc(1, sizeof(tListas));

  l->vetDocumentos = calloc(100, sizeof(tDocumento *));
  l->qtd_docs_alocados = 100;
  l->qtd_docs_lidos = 0;
  l->hash = Hash_cria();
  return l;
}

void Listas_gera_binario(tListas * l, char * nomeBin){
 FILE*arqIndices=fopen(nomeBin,"wb");
 if(!arqIndices){
  exit(1);
 }
  Hash_escreve_bin(l->hash,arqIndices);
  fclose(arqIndices);
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
    l = Listas_adiciona_doc(l, doc);
    printf("\nVOU LER ARQUIVO : %s\n", path);
    printf("TIPO DA NOTICIA : %s\n", classe);
    // ao sair dessa funcao temos uma lista
    l = Listas_ler_noticia(arqConteudoDoc, l, doc);
  }
  return l;
}


tListas *Listas_ler_noticia(FILE *arqDoc, tListas *l, tDocumento *d)
{
  while (1)
  {
    char palavra[50];
    memset(palavra, '\0', sizeof(char));

    fscanf(arqDoc, "%s", palavra);
    d = Documento_adiciona_palavra(d, palavra);
    Hash_adiciona_palavra(l->hash, palavra, Documento_get_indice(d));
    if (feof(arqDoc))
    {
      break;
    }
  }
  // Documento_imprime_palavras(d);
  printf("LI ARQ N '%d'\n", Documento_get_indice(d));
  fclose(arqDoc);
  return l;
}
tHashPalavras *Listas_get_hash(tListas *lista)
{
  return lista->hash;
}

void Listas_busca_noticia(tListas * lista, char * frase){
  char * aux;
  tHashPalavras * hash=Listas_get_hash(lista);
  aux =strtok(frase," ");
  int indice,i=0;
  int indiceDoc=0;
  

  //ao sair desse laço temos o valor os valores tfidf para aquela busca em todos os documentos
  while(i<lista->qtd_docs_lidos){
    int soma_Tf_idf_digitadas=0;
    //Ao sair desse laço temos o valor de um tf idf para aquela busca em um documento
    while(aux){
      if(Documento_Tem_palavra_documento(lista->vetDocumentos[i],aux)){
        tPalavra *palavra=Hash_get_palavra(Hash_get_no_palavra(hash,indice));
          soma_Tf_idf_digitadas+=Palavra_get_tf_idf(palavra,indiceDoc);
      }
      aux=strtok(NULL," ");
    }
    //imprimir os indices ordenados conformes os 10 primeiros valores
    //ImprimeBusca();
    indiceDoc++;
  }
  //qsort(vet_tf_idf,lista->qtd_docs_lidos,sizeof(double),comparaDouble);
  //ImprimeBusca(vet_tf_idf);
}
tListas *Listas_calcula_tf_idfs(tListas *l)
{

  tHashPalavras *hash = Listas_get_hash(l);
  for (int i = 0; i < Hash_get_idc_max(hash); i++)
  {
    if (Hash_get_no_palavra(hash, i) != NULL)
    {
      tListaPalavra *temp = Hash_get_no_palavra(hash, i);
      while (temp != NULL)
      {
        tPalavra *p = Hash_get_palavra(temp);
        p = Palavra_constroi_todos_TFIDFs(p, l->qtd_docs_lidos);
        temp = Hash_atribui_prox_no(temp);
      }
    }
  }

  // ESSA SEGUNDA PARTE DA FUNÇÃO ATRIBUI OS VALORES CALCULADOS DE TD-IDF PRA CADA PALAVRA DE CADA DOCUMENTO
  char palTemp[50];
  int idcTemp;
  double tfidf;
  for (int i = 0; i < l->qtd_docs_lidos; i++)
  {
    printf("\n\n----------DOC %d -----------------\n\n", i);
    for (int j = 0; j < Documento_get_qtd_palavras(l->vetDocumentos[i]); j++)
    {
      strcpy(palTemp, Documento_get_nome_palavra(l->vetDocumentos[i], j));
      idcTemp = Hash_cria_indice(palTemp);

      tListaPalavra *temp = Hash_get_no_palavra(hash, idcTemp);
      while (temp != NULL)
      {
        tPalavra *Palavra = Hash_get_palavra(temp);
        char nomePal[50];
        strcpy(nomePal, Palavra_get_nome(Palavra));

        if (strcmp(nomePal, palTemp) == 0)
        {
          tfidf = Palavra_get_tf_idf(Palavra, Documento_get_indice(l->vetDocumentos[i]));
          printf("%s TF: %lf\n", nomePal, tfidf);
          l->vetDocumentos[i] = Documento_atribui_tf_idf(l->vetDocumentos[i], j, tfidf);
          // Documento_imprime_palavras(l->vetDocumentos[i]);
        }
        temp = Hash_atribui_prox_no(temp);
      }
    }
  }

  return l;
}

void Listas_imprime_relatorio_palavra(char *nome, tListas *l)
{

  tPalavra *p = Hash_procura_palavra(nome, l->hash);
  printf("\n\nPALAVRA '%s':\n\n", Palavra_get_nome(p));
  printf("Qtd de docs q aparece: %d\n", Palavra_get_qtd_docs_q_aparece(p));
}

int ordena(const void *docA, const void *docB)
{
  tDocsAux A=*(tDocsAux*)docA;
  tDocsAux B=*(tDocsAux*)docB;

    return (B.qtd_palavras - A.qtd_palavras);

}

void Listas_imprime_relatorio_documentos(tListas *l)
{
  l->vetDocsAux=calloc(l->qtd_docs_lidos, sizeof(tDocsAux));
    for (int i = 0; i < l->qtd_docs_lidos; i++)
    {
        l->vetDocsAux[i].qtd_palavras=Documento_get_qtd_palavras_total(l->vetDocumentos[i]);
        l->vetDocsAux[i].idc=Documento_get_indice(l->vetDocumentos[i]);
    }
    qsort(l->vetDocsAux, l->qtd_docs_lidos, sizeof(tDocumento *), ordena);

    printf("\n10 DOCUMENTOS MAIS LONGOS: \n");
    int idc, qtd_palavras;
    for (int i=0; i<10; i++){
      idc=l->vetDocsAux[i].idc;
      qtd_palavras=l->vetDocsAux[i].qtd_palavras;
      //Documento_imprime(l->vetDocumentos[i], i+1);
      printf("%d: Documento '%s' ---> %d palavras", i+1, Documento_get_nome(l->vetDocumentos[idc]), l->vetDocsAux[i].qtd_palavras);
      printf("     / Classe: %s\n", Documento_get_classe(l->vetDocumentos[idc])) ;
    }
    int j=1;
    printf("\n\n10 DOCUMENTOS MAIS CURTOS: \n");
    for (int i=l->qtd_docs_lidos-1; i>l->qtd_docs_lidos-10; i--){
      j++;
      //Documento_imprime(l->vetDocumentos[i], j);
      printf("%d: Documento '%s' ---> %d palavras", i+1, Documento_get_nome(l->vetDocumentos[idc]), l->vetDocsAux[i].qtd_palavras);
      printf("     / Classe: %s\n", Documento_get_classe(l->vetDocumentos[idc])) ;

    }
  free(l->vetDocsAux);
}