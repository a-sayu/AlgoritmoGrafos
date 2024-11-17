#ifndef G_MATRIZ_H
#define G_MATRIZ_H

// Estrutura do Grafo
typedef struct {
    // Array de Array (Matriz)
    int **adj;
    // Vértices
    int vert;
} Grafo;

/**
 * @brief Ponteiro para o grafo
 */
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

/**
 * @brief Função para ler uma inserção de grafo
 * 
 * @return pont_grafo grafo com vertices, arestas e conexões
 */
pont_grafo ler_grafo();

#endif