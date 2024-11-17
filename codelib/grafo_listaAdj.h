#ifndef G_LISTA_H
#define G_LISTA_H

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
 * @brief Funçao auxiliar para liberar os nós encadeadas
 * 
 * @param lista lista a ser liberada
 */
void libera_lista(pont_no lista);

/**
 * @brief Funçao para destruir o grafo
 * 
 * @param grafo grafo que vai ser destruido
 */
void destruir_grafo(pont_grafo grafo);

/**
 * @brief Funçao auxiliar para criar nós para serem apontados
 * 
 * @param lista 
 * @param v 
 * @return pont_no 
 */
pont_no inserir_na_lista(pont_no lista, int v);

/**
 * @brief 
 * 
 * @param grafo 
 * @param u 
 * @param v 
 */
void inserir_aresta(pont_grafo grafo, int u, int v);

/**
 * @brief 
 * 
 * @param lista 
 * @param v 
 * @return pont_no 
 */
pont_no remover_da_lista(pont_no lista, int v);

/**
 * @brief 
 * 
 * @param grafo 
 * @param u 
 * @param v 
 */
void remover_aresta(pont_grafo grafo, int u, int v);

/**
 * @brief 
 * 
 * @param grafo 
 * @param u 
 * @param v 
 * @return int 
 */
int verificar_aresta(pont_grafo grafo, int u, int v);

/**
 * @brief 
 * 
 * @param grafo 
 */
void imprimir_arestas(pont_grafo grafo);

int *encontrar_componentes(pont_grafo grafo);

void visita_recursiva(pont_grafo, int *componentes, int componente, int v);

#endif