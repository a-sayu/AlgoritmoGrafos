#include <stdlib.h>
#include "grafo_matrizAdj.h"

// Implementação das Funções

pont_grafo criar_grafo(int n) {
    int linha, coluna;
    pont_grafo grafo = malloc(sizeof(Grafo));
    grafo->vert = n;

    // Alocou n ponteiros, representando as linhas
    grafo->adj = malloc(n *sizeof(int*));

    // Para cada linha, alocou um vetor representando as colunas
    for(linha = 0; linha < n; linha++)
        grafo->adj[linha] = malloc (n* sizeof(int));
    
    // Atribuindo '0' a todas as posições da matriz
    for(linha = 0; linha < n; linha++)
        for (coluna = 0; coluna < n; coluna++)
            grafo->adj[linha][coluna] = 0;

    return grafo;
}

void destruir_grafo(pont_grafo grafo) {
    int linha;

    // Libera os ponteiros
    for (linha = 0; linha < grafo->vert; linha++)
        free(grafo->adj[linha]);

    // libera a matriz
    free(grafo->adj);

    // Libera a estrutura grafo
    free(grafo);
}

void inserir_aresta(pont_grafo grafo, int u, int v) {
    grafo->adj[u][v] = 1;
    grafo->adj[v][u] = 1;
}

void remover_aresta(pont_grafo grafo, int u, int v) {
    grafo->adj[u][v] = 0;
    grafo->adj[v][u] = 0;
}

int verificar_aresta(pont_grafo grafo, int u, int v) {
    return grafo->adj[u][v];
}

pont_grafo ler_grafo() {
    int vertices, arestas, i, u, v;
    pont_grafo grafo;
    scanf("%d %d", &vertices, &arestas);
    grafo = criar_grafo(vertices);
    for (i = 0; i < arestas; i++) {
        scanf("%d %d", &u, &v);
        inserir_aresta(grafo, u, v);
    }
    return grafo;
}

void imprimir_arestas(pont_grafo grafo) {
    int u, v;
    for(u = 0; u < grafo->vert; u++)
        for (v = u+1; v < grafo->vert; v++)
            if (grafo->adj[u][v])
                printf("{%d,%d}", u, v);
}


///////////////////////////////

/**
 * @brief Funçao para ver quantos vizinhos u tem.
 * 
 * @param grafo que esta sendo observado
 * @param u vértice que esta sendo observado
 * @return int O número de vizinhos que um vértice u tem
 */
int grau (pont_grafo grafo, int u) {
    int v, grau = 0;
    for (v = 0; v < grafo->vert; v++)
        if (grafo->adj[u][v]) grau++;
    return grau;
}

/**
 * @brief Função que verifica o vértice com a maior quantidade de vizinhos
 * 
 * @param grafo que esta sendo observado
 * @return int O vertice com o maior numero de vizinhos.
 */
int mais_popular(pont_grafo grafo) {
    int u, vert_popular, grau_maior, grau_atual;
    vert_popular = 0;
    grau_maior = grau(grafo, 0);
    for (u = 1; u < grafo->vert; u++) {
        grau_atual = grau(grafo, u);
        if (grau_atual > grau_maior) {
            grau_maior = grau_atual;
            vert_popular = u;
        }
    }
    return vert_popular;
}

/**
 * @brief Função que imprime amigos de amigos de u
 * 
 * @param grafo sendo observado
 * @param u vertice que esta sendo observado
 */
void imprimir_recomendacoes(pont_grafo grafo, int u) {
    int v, w;
    // Ele percorre os vertices procurando vizinhos de u
    for (v = 0; v < grafo->vert; v++)
        if (grafo->adj[u][v])
            for (w = 0; w < grafo->vert; w++) // percorre os vertices procurando amigos dos amigos encontrados
                if (grafo->adj[v][w] && w != u && !grafo->adj[u][w])
                    printf("%d\n", w);
}

