#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaAdj.h"

pont_grafo criar_grafo(int n) {
    int i;
    pont_grafo grafo = malloc(sizeof(Grafo));
    grafo->n = n;
    grafo->adjacencia = malloc(n*sizeof(pont_no));
    for (i = 0; i < n; i++)
        grafo->adjacencia[i] = NULL; // faz apontar para nada
    return grafo;
}

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

int *encontrar_componentes(pont_grafo grafo) {
    int i, c = 0, *componentes = malloc(grafo->n * sizeof(int));
    for (i = 0; i < grafo->n; i++)
        componentes[i] = -1;
    for (i = 0; i < grafo->n; i++)
        if (componentes[i] == -1) {
            visita_recursiva(grafo, componentes, c, i);
            c++;
        }
    return componentes;
}

void visita_recursiva(pont_grafo grafo, int *componentes, int comp, int v) {
    pont_no t;
    componentes[v] = comp;
    for(t = grafo->adjacencia; t != NULL; t = t->prox)
        if (componentes[t->vert] == -1) visita_recursiva(grafo, componentes, comp, t->vert);
}

