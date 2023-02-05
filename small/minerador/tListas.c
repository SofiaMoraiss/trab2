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
  tNoAux *vetDocsAux;
  tNoAux *vetPalavrasAux;
};

struct noAux
{
  int idc;
  int valor;
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
  return l;
}

tListas *Listas_constroi()
{
  tListas *l = calloc(1, sizeof(tListas));

  l->vetDocumentos = calloc(100, sizeof(tDocumento *));
  l->qtd_palavras_lidas = 0;
  l->qtd_docs_alocados = 100;
  l->qtd_docs_lidos = 0;
  l->hash = Hash_cria();
  return l;
}

void Listas_gera_binario(tListas *l, char *nomeBin)
{
  FILE *arqIndices = fopen(nomeBin, "wb");
  if (!arqIndices)
  {
    printf("Erro! não foi possivel encontrar o arquivo %s", nomeBin);
    return;
  }
  Hash_escreve_bin(l->hash, arqIndices);
  fwrite(&l->qtd_docs_lidos, sizeof(int), 1, arqIndices);
  for (int i = 0; i < l->qtd_docs_lidos; i++)
  {
    Documento_escreve_bin(l->vetDocumentos[i], arqIndices);
  }
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
  fclose(arqDoc);
  return l;
}
tHashPalavras *Listas_get_hash(tListas *lista)
{
  return lista->hash;
}

void Listas_busca_noticia(tHashPalavras *hash, int qtd, tDocumento **vetDocumento)
{
  Docf **vet_soma_busca = calloc(qtd, sizeof(Docf *));
  Docf_inicializa(vet_soma_busca, qtd);
  int idcDoc;
  double tf_idf;
  char frase[50];
  char c;
  int qtdPalavraDgt = 0;
  do
  {
    scanf("%s%c", frase, &c);
    tPalavra *palavra = Hash_procura_palavra(frase, hash);
    if (!palavra)
    {
      if (c == '\n')
      {
        break;
      }
      continue;
    }
    qtdPalavraDgt++;

    for (int i = 0; i < Palavra_get_qtd_docs_q_aparece(palavra); i++)
    {
      idcDoc = Palavra_get_idc_doc(palavra, i);
      Documento_atribui_idc(vet_soma_busca[idcDoc], idcDoc);
      tf_idf = Palavra_get_tf_idf(palavra, i);
      Documento_soma_tfidf(vet_soma_busca, idcDoc, tf_idf);
    }
  } while (c != '\n');
  if (qtdPalavraDgt != 0)
  {
    qsort(vet_soma_busca, qtd, sizeof(Docf *), Documento_compara);
    Documento_imprime_docf(vet_soma_busca, qtd, vetDocumento);
    for (int i = 0; i < qtd; i++)
    {
      free(vet_soma_busca[i]);
    }
    free(vet_soma_busca);
  }
}

tDocumento *Listas_atribui_idfs_doc_clas(tHashPalavras *hash, tDocumento *d, int qtd, char **vetP)
{

  int tf = 0, j = 0, n = qtd, df, i = Documento_get_qtd_palavras(d);
  double idf = 10.0;
  for (; j < i; j++)
  {
    tf = Documento_get_ocorrencia_palavra(d, vetP[j]);
    tPalavra *p = Hash_procura_palavra(vetP[j], hash);
    df = Palavra_get_qtd_docs_q_aparece(p);
    idf = Palavra_calcula_1tf_idf(tf, qtd, df);
    Documento_atribui_tf_idf(d, vetP[j], idf);
    printf("PALAVRA: %s   IDF: %lf\n", Documento_get_nome_palavra(d, j), idf);
  }
  return d;
}

int ordena(const void *docA, const void *docB)
{
  tNoAux A = *(tNoAux *)docA;
  tNoAux B = *(tNoAux *)docB;

  return (B.valor - A.valor);
}

void Listas_classifica_noticia(tHashPalavras *hash, int qtd, tDocumento **vetDocumento)
{
  int i = 0, qtdAloc = 100;
  char **vetP = calloc(qtdAloc, sizeof(char *));
  char palavra[50], c;
  tDocumento *d = Documento_constroi("clas", "ind", qtd);
  do
  {
    scanf("%s%c", palavra, &c);
    d = Documento_adiciona_palavra(d, palavra);
    if (i >= qtdAloc)
    {
      qtdAloc *= 2;
      vetP = realloc(vetP, qtdAloc * sizeof(char *));
    }
    vetP[i] = calloc(50, sizeof(char));
    strcpy(vetP[i], palavra);
    Documento_adiciona_palavra(d, palavra);
    i++;

  } while (c != '\n');

  Listas_atribui_idfs_doc_clas(hash, d, qtd, vetP);

  tNoAux *vetAux = calloc(qtd, sizeof(tNoAux));
  for (int j = 0; j < qtd; j++)
  {
    vetAux[i].valor = Documento_calcula_cosseno(d, vetDocumento[j]);
    vetAux[i].idc = Documento_get_indice(vetDocumento[j]);
  }
  qsort(vetAux, qtd, sizeof(tNoAux), ordena);

  for (int j = 0; j < i; j++)
  {
    free(vetP[j]);
  }
  free(vetP);
  Documento_destroi(d);
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

        int idcDoc;
        double idf;
        for (int i = 0; i < Palavra_get_qtd_docs_q_aparece(p); i++)
        {
          idcDoc = Palavra_get_idc_doc(p, i);
          idf = Palavra_get_tf_idf(p, i);
          l->vetDocumentos[idcDoc] = Documento_atribui_tf_idf(l->vetDocumentos[idcDoc], Palavra_get_nome(p), idf);
        }

        temp = Hash_atribui_prox_no(temp);
      }
    }
  }

  return l;
}

void Listas_imprime_relatorio_palavra(tHashPalavras *hash)
{
  char nome[100];
  scanf("%s",nome);
  scanf("%*c");
  tPalavra *p = Hash_procura_palavra(nome, hash);

  printf("\n\nPALAVRA '%s':\n\n", Palavra_get_nome(p));
  printf("Qtd de docs q aparece: %d\n", Palavra_get_qtd_docs_q_aparece(p));

}
  int Listas_compara_no_aux(const void *docA, const void *docB)
  {
    tNoAux A = *(tNoAux *)docA;
    tNoAux B = *(tNoAux *)docB;

    return (B.valor - A.valor);
}

  void Listas_imprime_relatorio_documentos(tHashPalavras * l, tDocumento **vetDocumentos, int qtd)
  {
    tNoAux *vetDocsAux = calloc(qtd, sizeof(tNoAux));
    for (int i = 0; i < qtd; i++)
    {
      vetDocsAux[i].valor = Documento_get_qtd_palavras_total(vetDocumentos[i]);
      vetDocsAux[i].idc = Documento_get_indice(vetDocumentos[i]);
    }
    qsort(vetDocsAux, qtd, sizeof(tDocumento *), Listas_compara_no_aux);

    printf("\n10 DOCUMENTOS MAIS LONGOS: \n");
    int idc, qtd_palavras;
    for (int i = 0; i < 10; i++)
    {
      idc = vetDocsAux[i].idc;
      qtd_palavras = vetDocsAux[i].valor;
      printf("%d: Documento '%s' ---> %d palavras", i + 1, Documento_get_nome(vetDocumentos[idc]), vetDocsAux[i].valor);
      printf("     / Classe: %s\n", Documento_get_classe(vetDocumentos[idc]));
    }
    int j = 1;
    printf("\n\n10 DOCUMENTOS MAIS CURTOS: \n");
    for (int i = qtd - 1; i > qtd - 10; i--)
    {
      j++;
      printf("%d: Documento '%s' ---> %d palavras", i + 1, Documento_get_nome(vetDocumentos[idc]), vetDocsAux[i].valor);
      printf("     / Classe: %s\n", Documento_get_classe(vetDocumentos[idc]));
    }
    free(vetDocsAux);
  }
  void Listas_imprime_saida(tListas * l)
  {
    printf("QUANTIDADE DE DOCUMENTOS: %d\n\n", l->qtd_docs_lidos);
    printf("QUANTIDADE DE PALAVRAS DIFERENTES: %d\n\n", Hash_get_qtdPalavras(l->hash));
  }
