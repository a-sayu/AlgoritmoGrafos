#include <stdlib.h>

// Estrutura do Grafo
typedef struct {
    // Array de Array (Matriz)
    int **adj;
    // Vértices
    int vert;
} Grafo;

// Ponteiro para o grafo
typedef Grafo *pont_grafo;

/** 
  * @brief Função para criar o grafo
  * 
  * @param n número de vértices do grafo
 **/
pont_grafo criar_grafo(int n);

/**
  * @brief Função para destruir um grafo
  * 
  * @param grafo grafo que será destruido
 **/
void destruir_grafo(pont_grafo grafo);

/**
  * @brief Função que insere uma aresta
  * 
  * Ele conecta os dois vértices fazendo eles
  * afirmarem na matriz que eles se conhecem
  * 
  * @param grafo grafo que está tendo uma aresta inserida
  * @param u vértice que fará parte da aresta
  * @param v vértice que fará parte da aresta
 **/
void inserir_aresta(pont_grafo grafo, int u, int v);

/**
  * @brief Função que remove uma aresta
  * 
  * Ele desconecta dois vértices fazendo eles
  * afirmarem na matriz que não se conhecem
  * 
  * @param grafo grafo que está tendo uma aresta removida
  * @param u vértice que não fará mais parte da aresta
  * @param v vértice que não fará mais parte da aresta
 **/
void remover_aresta(pont_grafo grafo, int u, int v);

/**
  * @brief Função que retorna se há aresta
  * 
  * @param grafo grafo que está sendo observado
  * @param u vértice que está sendo observado
  * @param v vértice que está sendo observado
  * @return int 1: Há aresta || 0: Não há aresta
 **/
int verificar_aresta(pont_grafo grafo, int u, int v);

/**
  * @brief Função que imprime as arestas do grafo
  *
  * Vai percorrer cada linha, para encontrar
  * uma conexão entre os dois vértices
  * evitando de pegar o mesmo vertice
  * com o outro vertice sendo +1 a frente
  * 
  * @param grafo grafo a ser precorrido
 **/
void imprimir_arestas(pont_grafo grafo);

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

/**
 * @brief Função para ler uma inserção de grafo
 * 
 * @return pont_grafo grafo com vertices, arestas e conexões
 */
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