/*
 * Módulo: grafo.h;
 *
 * Estudante: Eduardo Henrique Costa Moresi;
 * Matrícula: 14/0019286;
 *
 * Data: 28/04/2016;
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#include <lista_simples.h>
#include <lista_dupla.h>

#define FOUND 1
#define MIN 0.000001

enum tipo_vertice {
	ORIGEM, NAO_ORIGEM
};

typedef struct Grafo {
	TpListaSimples vertices;
	TpListaSimples vertices_origem;
	TpListaDupla *adjacencia;
	int numero_vertices;
	int numero_origens;
	int tam_vetor_lista;	
}TpGrafo;

int le_grafo(FILE *input, TpGrafo *grafo);
int escreve_grafo(FILE *output, TpGrafo *grafo);
int insere_vertex(TpGrafo *grafo, TpVertex vertice, int type);
int remove_vertex(TpGrafo *grafo, TpVertex *vertice, char *nome);
int insere_aresta(TpGrafo *grafo, char *origem, char *destino, float peso);
int remove_aresta(TpGrafo *grafo, char *origem, char *destino);
float calculaDistancia(TpGrafo *grafo, char *origem, char *destino);
int verifica_caminho(TpGrafo *grafo, char *origem, char *destino);
int DFS_rec_caminho(TpGrafo *grafo, TpListaSimples *l_simples, TpListaDupla *lista, char *origem, char *destino);
int grafoConsistente(TpGrafo *grafo);
int grafoConexo(TpGrafo *grafo);
void DFS(TpGrafo *grafo, TpListaSimples *lista, int *count);
void DFS_rec(TpGrafo *grafo, TpListaSimples *l_simples, TpListaDupla *lista, int *count);
int destroi_grafo(TpGrafo *grafo);

#endif /* GRAFO_H_ */
