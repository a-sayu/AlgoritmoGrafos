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

pont_grafo criar_grafo_peso(int n) {
    int linha, coluna;
    pont_grafo grafo = malloc(sizeof(Grafo));
    grafo->vert = n;

    // Alocou n ponteiros, representando as linhas
    grafo->adj = malloc(n *sizeof(int*));

    // Para cada linha, alocou um vetor representando as colunas
    for(linha = 0; linha < n; linha++)
        grafo->adj[linha] = malloc (n* sizeof(int));
    
    // Atribuindo 'INT_MAX' a todas as posições da matriz, para indicar não ter uma aresta
    for(linha = 0; linha < n; linha++)
        for (coluna = 0; coluna < n; coluna++)
            grafo->adj[linha][coluna] = INT_MAX;

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

void inserir_aresta_direcao(pont_grafo grafo, int u, int v) {
    grafo->adj[u][v] = 1;
}

void inserir_aresta_direcao_peso(pont_grafo grafo, int u, int v, int peso) {
    grafo->adj[u][v] = peso;
}

void remover_aresta(pont_grafo grafo, int u, int v) {
    grafo->adj[u][v] = 0;
    grafo->adj[v][u] = 0;
}

void remover_aresta_direcao(pont_grafo grafo, int u, int v) {
    grafo->adj[u][v] = 0;
}

void remover_aresta_direcao_peso(pont_grafo grafo, int u, int v) {
    grafo->adj[u][v] = INT_MAX;
}

int verificar_aresta(pont_grafo grafo, int u, int v) {
    return grafo->adj[u][v];
}

int verificar_aresta_peso(pont_grafo grafo, int u, int v) {
    if (grafo->adj[u][v] != INT_MAX) return 1;
    return 0;
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

pont_grafo ler_grafo_direcao() {
    int vertices, arestas, i, u, v;
    pont_grafo grafo;
    scanf("%d %d", &vertices, &arestas);
    grafo = criar_grafo(vertices);
    for (i = 0; i < arestas; i++) {
        scanf("%d %d", &u, &v);
        inserir_aresta_direcao(grafo, u, v);
    }
    return grafo;
}

pont_grafo ler_grafo_direcao_peso() {
    int vertices, arestas, i, u, v, peso;
    pont_grafo grafo;
    scanf("%d %d", &vertices, &arestas);
    grafo = criar_grafo(vertices);
    for (i = 0; i < arestas; i++) {
        scanf("%d %d %d", &u, &v, &peso);
        inserir_aresta_direcao_peso(grafo, u, v, peso);
    }
    return grafo;
}

void imprimir_arestas(pont_grafo grafo) {
    int u, v;
    for(u = 0; u < grafo->vert; u++)
        for (v = u+1; v < grafo->vert; v++)
            if (grafo->adj[u][v])
                printf("{%d,%d}\n", u, v);
}

void imprimir_arestas_direcao(pont_grafo grafo) {
    int u, v;
    for(u = 0; u < grafo->vert; u++)
        for (v = 0; v < grafo->vert; v++)
            if (grafo->adj[u][v])
                printf("{%d,%d}\n", u, v);
}

void imprimir_arestas_direcao_peso(pont_grafo grafo) {
    int u, v;
    for(u = 0; u < grafo->vert; u++)
        for (v = 0; v < grafo->vert; v++)
            if (grafo->adj[u][v] != INT_MAX)
                printf("{%d,%d} = %d\n", u, v, grafo->adj[u][v]);
}


///////////////////////////////

// TODO: peso + direcao

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

int grau_peso (pont_grafo grafo, int u) {
    int v, grau = 0;
    for (v = 0; v < grafo->vert; v++)
        if (grafo->adj[u][v] != INT_MAX) grau++;
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

///////////////////////////////

// TODO: peso + direcao

int encontrar_caminho(pont_grafo grafo, int u, int v) {
    int encontrado, i, *visitado =malloc(grafo->vert * sizeof(int));
    for (i = 0; i < grafo->vert; i++) visitado[i] = 0;
    encontrado = busca_recursiva(grafo, visitado, u, v);
    free(visitado);
    return encontrado;
}

int busca_recursiva(pont_grafo grafo, int *visitado, int u, int v) {
    int i;
    if (u == v) return 1;
    visitado[u] = 1;
    for (i = 0; i < grafo->vert; i++)
        if (grafo->adj[u][i] && !visitado[i])
            if (busca_recursiva(grafo, visitado, i, v)) return 1;
    return 0;
}

//////////////////////////////

// busca em profundidade, busca em largura, dijikstra, Arvore Geradora Mínima
