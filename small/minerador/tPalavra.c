#include "tPalavra.h"
#include "tHashPalavras.h"
#include "recalloc.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct palavra
{
    char nome[50];
    int qtd_documentos_alocados;
    int qtd_documentos_q_aparece;
    int n_do_ultimo_doc_q_aparece;

    int *vetDocumentos; // indices dos documentos q aparece
    int *qtd_ocorrencias; // frequencia de uma palavra em cada documento
    double *tf_idf;
};

int Palavra_compara(const void *ptr, const void *ptr2)
{
    tPalavra *p1;
    tPalavra *p2;
    p1 = *(tPalavra **)ptr;
    p2 = *(tPalavra **)ptr2;
    return strcmp(p1->nome, p2->nome);
}
//retorna o indice do documento da iesima posicao 
int Palavra_get_documento(tPalavra * palavra, int idcDoc){
        return palavra->vetDocumentos[idcDoc];
}
tPalavra *Palavra_constroi(char *nome)
{
    tPalavra *d = calloc(1, sizeof(tPalavra));
    strcpy(d->nome, nome);
    d->qtd_ocorrencias = calloc(100, sizeof(int));
    d->tf_idf = calloc(100, sizeof(double));
    d->vetDocumentos = calloc(100, sizeof(int));

    d->qtd_documentos_alocados = 100;
    d->qtd_documentos_q_aparece = 0;
    d->n_do_ultimo_doc_q_aparece = -1;
    return d;
}

void Palavra_destroi(tPalavra *palavra)
{
    free(palavra->qtd_ocorrencias);
    free(palavra->tf_idf);
    free(palavra->vetDocumentos);
    free(palavra);
}

char *Palavra_get_nome(tPalavra *palavra)
{
    return palavra->nome;
}

double Palavra_get_tf_idf(tPalavra *palavra, int doc)
{

    return palavra->tf_idf[doc];
    return 10;
}

double *Palavra_get_vetTFIDF(tPalavra *p) { return p->tf_idf; }

int Palavra_get_qtd_docs_q_aparece(tPalavra *p) { return p->qtd_documentos_q_aparece; }

int Palavra_get_ocorrencia(tPalavra *p, int doc)
{

    for (int i = 0; i < p->qtd_documentos_q_aparece; i++)
    {
        if (p->vetDocumentos[i] == doc)
        {
            return p->qtd_ocorrencias[i];
        }
    }
    return 0;
}

void Palavra_adiciona_ocorrencia(tPalavra *p, int doc)
{

    if (p->qtd_documentos_q_aparece == p->qtd_documentos_alocados)
    {
        p->qtd_documentos_alocados *= 2;

        p->vetDocumentos = realloc(p->vetDocumentos, p->qtd_documentos_alocados * sizeof(int));
        p->qtd_ocorrencias = realloc(p->qtd_ocorrencias, p->qtd_documentos_alocados * sizeof(int));
        p->tf_idf = realloc(p->tf_idf, p->qtd_documentos_alocados * sizeof(double));
        for (int i = p->qtd_documentos_q_aparece; i < p->qtd_documentos_alocados; i++)
        {
            p->qtd_ocorrencias[i] = 0;            
            p->tf_idf[i] = 0.0;            
            p->vetDocumentos[i] = 0;            

        }

        // p->vetDocumentos = recalloc(p->vetDocumentos, p->qtd_documentos_alocados, sizeof(int));
        // p->qtd_ocorrencias = recalloc(p->qtd_ocorrencias, p->qtd_documentos_alocados, sizeof(int));
        // p->tf_idf = recalloc(p->tf_idf, p->qtd_documentos_alocados, sizeof(double));
    }
    int idc = p->qtd_documentos_q_aparece;
    p->vetDocumentos[idc] = doc;
    p->qtd_ocorrencias[idc]++;
    if (p->n_do_ultimo_doc_q_aparece != doc)
    {
        p->qtd_documentos_q_aparece++;
    }
    p->n_do_ultimo_doc_q_aparece = doc;
}

void Palavra_imprime(tPalavra *p)
{
    printf("%s\n", p->nome);
    printf("INDICES :");
    for (int i = 0; i < p->qtd_documentos_q_aparece; i++)
    {
        printf("OCORRENCIAS :%d\n", p->qtd_ocorrencias[i]);
        printf("TF_IDF : %lf\n",p->tf_idf[i]);
        printf("NO DOCUMENTO:%d\n\n", p->vetDocumentos[i]);
        //printf("--------");
        
    }
    printf("\n");
}

tPalavra *Palavra_le_binario(FILE *arquivo)
{
     tPalavra *p = calloc(1, sizeof(tPalavra));
    fread(&p->n_do_ultimo_doc_q_aparece, sizeof(int), 1, arquivo);
    fread(&p->qtd_documentos_q_aparece, sizeof(int), 1, arquivo);
    p->vetDocumentos=calloc(p->qtd_documentos_q_aparece,sizeof(int));
    p->tf_idf=calloc(p->qtd_documentos_q_aparece,sizeof(double));
    p->qtd_ocorrencias=calloc(p->qtd_documentos_q_aparece,sizeof(int));
    int tam;
    fread(&tam,sizeof(int),1,arquivo);
    fread(p->nome, sizeof(char),tam, arquivo);
    fread(p->qtd_ocorrencias, sizeof(int), p->qtd_documentos_q_aparece, arquivo);
    fread(p->tf_idf, sizeof(double), p->qtd_documentos_q_aparece, arquivo);
    //printf("%d\n",p->qtd_documentos_q_aparece);
    // for(int i=0;i<p->qtd_documentos_q_aparece;i++){
    //     printf("O Q TA LENDO:%lf\n\n",p->tf_idf[i]);
    // }
    fread(p->vetDocumentos, sizeof(int), p->qtd_documentos_q_aparece, arquivo);

    return p;
}
int Palavra_get_tam(tPalavra *palavra)
{
    return strlen(Palavra_get_nome(palavra));
}
void Palavra_escreve_binario(tPalavra *p, FILE *arquivo)
{
    fwrite(&p->n_do_ultimo_doc_q_aparece, sizeof(int), 1, arquivo);
    fwrite(&p->qtd_documentos_q_aparece, sizeof(int), 1, arquivo);
    int tam=strlen(p->nome)+1;
    fwrite(&tam,sizeof(int),1,arquivo);
    fwrite(p->nome, sizeof(char), tam, arquivo);
    fwrite(p->qtd_ocorrencias, sizeof(int), p->qtd_documentos_q_aparece, arquivo);
    fwrite(p->tf_idf, sizeof(double), p->qtd_documentos_q_aparece, arquivo); // resolver função de criar tf_idf
    fwrite(p->vetDocumentos, sizeof(int), p->qtd_documentos_q_aparece, arquivo);
}
int Palavra_get_num_bytes()
{
    return sizeof(tPalavra);
}

int Palavra_get_idc_doc(tPalavra *p,int idc)
{
    return p->vetDocumentos[idc];
}

void Palavra_imprime_idfs(tPalavra * p){
    printf("--%d--\n\n",p->qtd_documentos_q_aparece);
    for (int i = 0; i < p->qtd_documentos_q_aparece; i++)
    {
        printf("APARECE NO DOC:%d TF-IDF[%d]= %lf  QTD_OC[%d]= %d\n",p->vetDocumentos[i], i, p->tf_idf[i], i, p->qtd_ocorrencias[i]);
    }
}

tPalavra *Palavra_constroi_todos_TFIDFs(tPalavra *p, int qtdTotalDocs)
{
    //printf("\n\nPALAVRA: ");
    //Palavra_imprime(p);
    //printf("QTD DOCS Q APARECE: %d\n", p->qtd_documentos_q_aparece);
    for (int i = 0; i < p->qtd_documentos_q_aparece; i++)
    {
        p->tf_idf[i] = Palavra_calcula_1tf_idf(p->qtd_ocorrencias[i], qtdTotalDocs, p->qtd_documentos_q_aparece);
        //printf("TF-IDF[%d]= %lf    QTD_OC[%d]= %d\n", i, p->tf_idf[i], i, p->qtd_ocorrencias[i]);
    }
    return p;
}

double Palavra_calcula_1tf_idf(int tf, int nTotaldeDocs, int qtdDocsAparece)
{

    float df = qtdDocsAparece;
    float n = nTotaldeDocs;
    double TF_IDF = 0.0;

    double idf = log((1.0 + n) / (1.0 + df))+1;

    TF_IDF = tf * idf;

    return TF_IDF;
}

tPalavra *Palavra_atribui_tf_idf(tPalavra*p, int idcDocClas, double idf){
    int ix=Palavra_get_idc_doc(p, idcDocClas);
    p->tf_idf[ix]=idf;
    return p;
}
