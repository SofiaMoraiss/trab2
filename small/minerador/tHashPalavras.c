#include "tHashPalavras.h"
#include "tListas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listaPalavra
{
    tPalavra *palavra;
    struct listaPalavra *next;
};

struct hashPalavras
{
    int qtdPalavrasLidas;
    tListaPalavra **hashmap_lista;
    int indiceMaximo;
};
tListaPalavra *Hash_get_no_palavra(tHashPalavras *hash, int idcHash)
{
    return hash->hashmap_lista[idcHash];
}
tListaPalavra **Hash_get_lista_palavra(tHashPalavras *hash)
{
    return hash->hashmap_lista;
}
int Hash_get_idc_max(tHashPalavras *hash)
{
    return hash->indiceMaximo;
}
void Hash_atribui_idcMax(tHashPalavras *hash, int idcMax)
{
    hash->indiceMaximo = idcMax;
}
tListaPalavra *Hash_atribui_prox_no(tListaPalavra *lista)
{
    return lista->next;
}

tPalavra *Hash_get_palavra(tListaPalavra *listaPalavra)
{
    return listaPalavra->palavra;
}

static char convMaiuscula(char c)
{
    return c = c - 32;
}

int Hash_cria_indice(char *p)
{
    int indice = 0;
    int cont = 0, aux = 0;
    while (cont < strlen(p))
    {
        aux = convMaiuscula(p[cont]);
        indice += aux;
        cont++;
    }
    return indice;
}

tHashPalavras *Hash_cria()
{
    tHashPalavras *hashPalavras = calloc(1, sizeof(tHashPalavras));
    hashPalavras->hashmap_lista = calloc(1, sizeof(tListaPalavra *));
    hashPalavras->qtdPalavrasLidas = 0;
    hashPalavras->indiceMaximo = 1;

    return hashPalavras;
}

void Hash_destroi(tHashPalavras *h)
{
    if (h == NULL)
    {
        return;
    }
    for (int i = 0; i < h->indiceMaximo; i++)
    {
        if (h->hashmap_lista[i] != NULL)
        {
            tListaPalavra *temp = h->hashmap_lista[i];
            tListaPalavra *temp_next = NULL;
            while (temp != NULL)
            {
                temp_next = temp->next;
                // ImprimePalavra(temp->palavra);
                Palavra_destroi(temp->palavra);
                free(temp);
                temp = temp_next;
            }
        }
    }
    free(h->hashmap_lista);
    free(h);
}
int Hash_obtem_qtdPalavras(tHashPalavras *hash)
{
    return hash->qtdPalavrasLidas;
}
void Hash_escreve_bin(tHashPalavras *hash, FILE *file)
{

    fwrite(&hash->qtdPalavrasLidas, sizeof(int), 1, file);
    fwrite(&hash->indiceMaximo, sizeof(int), 1, file);
    for (int i = 0; i < hash->indiceMaximo; i++)
    {
        if (hash->hashmap_lista[i] != NULL)
        {
            tListaPalavra *temp = hash->hashmap_lista[i];
            tListaPalavra *temp_next = NULL;
            while (temp != NULL)
            {
                temp_next = temp->next;
                Palavra_escreve_binario(temp->palavra, file);
                temp = temp_next;
            }
        }
    }
}
tHashPalavras *Hash_le_bin(FILE * arqIndices)
{
    int qtd;
    int idcMax;
    tHashPalavras *hash = calloc(1,sizeof(tHashPalavras));
    fread(&hash->qtdPalavrasLidas, sizeof(int), 1, arqIndices);
    fread(&hash->indiceMaximo, sizeof(int), 1, arqIndices);
    hash->hashmap_lista=calloc(hash->indiceMaximo,sizeof(tListaPalavra*));
    for(int i=0; i<hash->qtdPalavrasLidas;i++){
        tPalavra *palavra = Palavra_le_binario(arqIndices);
        Hash_recria(hash, palavra);
    }
    return hash;
}

void Hash_recria(tHashPalavras *hashPalavras, tPalavra *pal)
{
    Palavra_imprime(pal);
    int indice = Hash_cria_indice(Palavra_get_nome(pal));

    // printf("'%s': indice %d\n", palavra, indice);
    if (hashPalavras->hashmap_lista[indice] == NULL)
    {
        hashPalavras->hashmap_lista[indice] = calloc(1, sizeof(tListaPalavra));
        hashPalavras->hashmap_lista[indice]->next = NULL;
        hashPalavras->hashmap_lista[indice]->palavra = pal;
    }
    else
    {
        tListaPalavra *lista = hashPalavras->hashmap_lista[indice];
        tListaPalavra *lista_anterior = NULL;
        while (lista != NULL)
        {

            if (strcmp(Palavra_get_nome(lista->palavra), Palavra_get_nome(pal)) == 0)
            {
                break;
            }
            lista_anterior = lista;
            lista = lista->next;
        }
        if (lista == NULL)
        {
            lista_anterior->next = calloc(1, sizeof(tListaPalavra));
            lista = lista_anterior->next;
            lista->next = NULL;
            lista->palavra = pal;
        }
    }
}
void Hash_adiciona_palavra(tHashPalavras *hashPalavras, char *palavra, int documento)
{
    int indice = Hash_cria_indice(palavra);
    // printf("'%s': indice %d\n", palavra, indice);
    if (indice > hashPalavras->indiceMaximo)
    {
        int i = hashPalavras->indiceMaximo;
        hashPalavras->indiceMaximo = indice + 1;
        hashPalavras->hashmap_lista = realloc(hashPalavras->hashmap_lista, (indice + 1) * sizeof(tListaPalavra *));
        for (; i < hashPalavras->indiceMaximo; i++)
        {
            hashPalavras->hashmap_lista[i] = NULL;
        }
    }
    if (hashPalavras->hashmap_lista[indice] == NULL)
    {
        hashPalavras->hashmap_lista[indice] = calloc(1, sizeof(tListaPalavra));
        hashPalavras->hashmap_lista[indice]->next = NULL;
        hashPalavras->hashmap_lista[indice]->palavra = Palavra_constroi(palavra); //// FREE N TA INDO
        Palavra_adiciona_ocorrencia(hashPalavras->hashmap_lista[indice]->palavra, documento);
        hashPalavras->qtdPalavrasLidas++;
    }
    else
    {
        tListaPalavra *lista = hashPalavras->hashmap_lista[indice];
        tListaPalavra *lista_anterior = NULL;
        while (lista != NULL)
        {
            if (strcmp(Palavra_get_nome(lista->palavra), palavra) == 0)
            {
                break;
            }
            lista_anterior = lista;
            lista = lista->next;
        }
        if (lista == NULL)
        {
            lista_anterior->next = calloc(1, sizeof(tListaPalavra));
            lista = lista_anterior->next;
            lista->next = NULL;
            lista->palavra = Palavra_constroi(palavra); //// FREE N TA FREEANDO
            hashPalavras->qtdPalavrasLidas++;
        }
        Palavra_adiciona_ocorrencia(lista->palavra, documento);
    }
}

void Hash_imprime(tHashPalavras *hashPalavras, int documento)
{
    // printf("doc: %d\n", documento);
    if (hashPalavras == NULL)
    {
        return;
    }
    // printf(" indice max: %d\n", hashPalavras->indiceMaximo);

    for (int i = 0; i < hashPalavras->indiceMaximo; i++)
    {
        // printf("3\n");
        if (hashPalavras->hashmap_lista[i] != NULL)
        {
            tListaPalavra *temp = hashPalavras->hashmap_lista[i];
            while (temp != NULL)
            {
                // printf("%s (%d)\n", get_nome(temp->palavra), get_ocorrencia(temp->palavra, documento));
                temp = temp->next;
            }
        }
    }
}

tPalavra *Hash_procura_palavra(char *nome, tHashPalavras *hash)
{

    int idcTemp = Hash_cria_indice(nome);

    tListaPalavra *temp = Hash_get_no_palavra(hash, idcTemp);
    while (temp != NULL)
    {
        tPalavra *Palavra = Hash_get_palavra(temp);
        char nomePal[50];
        strcpy(nomePal, Palavra_get_nome(Palavra));

        if (strcmp(nomePal, nome) == 0)
        {
            return Palavra;
        }
        temp = Hash_atribui_prox_no(temp);
    }
    return NULL;
}
int Hash_obtem_numBytes()
{
    return sizeof(tHashPalavras);
}