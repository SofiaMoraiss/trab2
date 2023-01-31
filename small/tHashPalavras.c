#include "tHashPalavras.h"
#include "tListas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listaPalavra {
    tPalavra* palavra;
    struct listaPalavra* next;
};

struct hashPalavras {
    tListaPalavra** hashmap_lista;
    int indiceMaximo;
};
tListaPalavra * ObtemNoPalavra(tHashPalavras * hash,int posicao){
    return hash->hashmap_lista[posicao];
}
tListaPalavra ** ObtemListaPalavra(tHashPalavras * hash){
    return hash->hashmap_lista;
}
int Obtem_idc_max(tHashPalavras * hash){
    return hash->indiceMaximo;
}
tListaPalavra* AtribuiProxNo(tListaPalavra * lista){
    return lista->next;
}
tPalavra * Obtem_palavra(tListaPalavra *listaPalavra){
    return listaPalavra->palavra;
}
static int criaIndice(char* p);

tHashPalavras* Hash_cria_palavras() {
    tHashPalavras* hashPalavras = calloc(1, sizeof(tHashPalavras));
    hashPalavras->hashmap_lista = calloc(1, sizeof(tListaPalavra*));

    hashPalavras->indiceMaximo = 1;

    return hashPalavras;
}


void destroiHashPalavras(tHashPalavras* h) {
    if (h == NULL) {
        return;
    }
    for (int i = 0; i < h->indiceMaximo; i++) {
        if (h->hashmap_lista[i] != NULL) {
            tListaPalavra* temp = h->hashmap_lista[i];
            tListaPalavra* temp_next = NULL;
            while (temp != NULL) {
                temp_next = temp->next;
                //ImprimePalavra(temp->palavra);
                //Palavra_destroi(temp->palavra);
                free(temp);
                temp = temp_next;
            }
        }
    }
    free(h->hashmap_lista);
    free(h);
}

void Hash_adiciona_palavra(tHashPalavras* hashPalavras, char* palavra, int documento) {
    int indice = criaIndice(palavra);
    // printf("'%s': indice %d\n", palavra, indice);
    if (indice > hashPalavras->indiceMaximo) {
        int i = hashPalavras->indiceMaximo - 1;
        hashPalavras->indiceMaximo = indice + 1;
        hashPalavras->hashmap_lista = realloc(hashPalavras->hashmap_lista, (indice + 1) * sizeof(tListaPalavra*));
        for (i; i < hashPalavras->indiceMaximo; i++) {
            hashPalavras->hashmap_lista[i] = NULL;
        }
    }
    if (hashPalavras->hashmap_lista[indice] == NULL) {
        hashPalavras->hashmap_lista[indice] = calloc(1, sizeof(tListaPalavra));
        hashPalavras->hashmap_lista[indice]->next = NULL;
        hashPalavras->hashmap_lista[indice]->palavra = Palavra_constroi(palavra);
        Adiciona_ocorrencia(hashPalavras->hashmap_lista[indice]->palavra, documento);

    } else {
        tListaPalavra* lista = hashPalavras->hashmap_lista[indice];
        tListaPalavra* lista_anterior = NULL;
        while (lista != NULL) {
            if (strcmp(get_nome(lista->palavra), palavra) == 0) {
                break;
            }
            lista_anterior = lista;
            lista = lista->next;
        }
        if (lista == NULL) {
            lista_anterior->next = calloc(1, sizeof(tListaPalavra));
            lista = lista_anterior->next;
            lista->next = NULL;
            lista->palavra = Palavra_constroi(palavra);
        }
        Adiciona_ocorrencia(lista->palavra, documento);
    }
}

void imprimeHash(tHashPalavras* hashPalavras, int documento) {
    printf("doc: %d\n", documento);
    if (hashPalavras == NULL) {
        return;
    }
    printf(" indice max: %d\n", hashPalavras->indiceMaximo);

    for (int i = 0; i < hashPalavras->indiceMaximo; i++) {
        // printf("3\n");
        if (hashPalavras->hashmap_lista[i] != NULL) {
            tListaPalavra* temp = hashPalavras->hashmap_lista[i];
            while (temp != NULL) {
                    printf("%s (%d)\n", get_nome(temp->palavra), get_ocorrencia(temp->palavra, documento));
                temp = temp->next;
            }
        }
    }
}


static char convMaiuscula(char c) {
    return c = c - 32;
}

static int criaIndice(char* p) {
    int indice = 0;
    int cont = 0, aux = 0;
    while (cont < strlen(p)) {
        aux = convMaiuscula(p[cont]);
        indice += aux;
        cont++;
    }
    return indice;
}
