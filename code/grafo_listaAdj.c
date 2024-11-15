#include <stdio.h>
#include <stdlib.h>

// Estrutura dos Nós da Lista
typedef struct No {
    // Vértice
    int vert;
    // Próximo Nó
    struct No *prox;
} No;

typedef No *pont_no;

// Estrutura do Grafo
typedef struct {
    // Vetor de ponteiros para a adjacencia
    pont_no *adjacencia;
    // Quantidade de Vértices
    int n;
} Grafo;

typedef Grafo *pont_grafo;

/**
 * @brief Funçao para criar um grafo
 * 
 * @param n quantidade de vértices
 * @return pont_grafo o grafo retornado
 */
pont_grafo criar_grafo(int n);

/**
 * @brief Funçao para destruir o grafo
 * 
 * @param grafo grafo que vai ser destruido
 */
void destruir_grafo(pont_grafo grafo);

void inserir_aresta(pont_grafo grafo, int u, int v);

void remover_aresta(pont_grafo grafo, int u, int v);

int verificar_aresta(pont_grafo grafo, int u, int v);

void imprimir_arestas(pont_grafo grafo);

pont_grafo criar_grafo(int n) {
    int i;
    pont_grafo grafo = malloc(sizeof(Grafo));
    grafo->n = n;
    grafo->adjacencia = malloc(n*sizeof(pont_no));
    for (i = 0; i < n; i++)
        grafo->adjacencia[i] = NULL; // faz apontar para nada
    return grafo;
}

/**
 * @brief Funçao auxiliar para liberar os nós encadeadas
 * 
 * @param lista lista a ser liberada
 */
void libera_lista(pont_no lista) {
    if (lista != NULL) {
        libera_lista(lista->prox);
        free(lista);
    }
}

void destruir_grafo(pont_grafo grafo) {
    int i;
    for (i = 0; i < grafo->n; i++)
        libera_lista(grafo->adjacencia[i]);
    free(grafo->adjacencia);
    free(grafo);
}

/**
 * @brief Funçao auxiliar para criar nós para serem apontados
 * 
 * @param lista 
 * @param v 
 * @return pont_no 
 */
pont_no inserir_na_lista(pont_no lista, int v) {
    pont_no novo = malloc(sizeof(No));
    novo->vert = v;
    novo->prox = lista;
    return novo;
}

void inserir_aresta(pont_grafo grafo, int u, int v) {
    grafo->adjacencia[v] = inserir_na_lista(grafo->adjacencia[v], u);
    grafo->adjacencia[u] = inserir_na_lista(grafo->adjacencia[u], v);
}

pont_no remover_da_lista(pont_no lista, int v) {
    pont_no proximo;
    if (lista == NULL) return NULL;
    else if (lista->vert == v) {
        proximo = lista->prox;
        free(lista);
        return proximo;
    }
    else {
        lista->prox = remover_da_lista(lista->prox, v);
        return lista;
    }
}

void remover_aresta(pont_grafo grafo, int u, int v) {
    grafo->adjacencia[u] = remover_da_lista(grafo->adjacencia[u], v);
    grafo->adjacencia[v] = remover_da_lista(grafo->adjacencia[v], u);
}

int verificar_arestas(pont_grafo grafo, int u, int v) {
    pont_no t;
    for (t = grafo->adjacencia[u]; t != NULL; t = t->prox)
        if (t->vert == v) return 1;
    return 0;
}

void imprimir_aresta(pont_grafo grafo) {
    int u;
    pont_no t;
    for (u = 0; u < grafo->n; u++)
        for(t = grafo->adjacencia[u]; t != NULL; t = t->prox)
            printf ("{%d, %d}\n", u, t->vert);
}



