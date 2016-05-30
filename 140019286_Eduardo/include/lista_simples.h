#ifndef LISTA_SIMPLES_H_
#define LISTA_SIMPLES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 100
#define ERRO -1
#define ERRO_F -1.0
#define INFINITO 9999999

enum visitado {
	VISITADO, EM_CURSO, NAO_VISITADO
};

typedef struct Vertex
{
	float distancia;
	int visitado;
	char nome[TAM_MAX]; /* Nome do vértice; */
	int id; /* Identificacao do vértice; */
}TpVertex;

typedef struct Celula
{
	TpVertex vertice;
	struct Celula *prox;
}celula;

typedef struct Lista
{
	int tam;
	celula *ini, *fim;
}TpListaSimples;

int cria_LS(TpListaSimples *l);
int insere_inicio_LS(TpListaSimples *l, TpVertex vertex);
int insere_fim_LS(TpListaSimples *l, TpVertex vertex);
int checa_vazia_LS(TpListaSimples *l);
int procura_id_LS(TpListaSimples *l, char *nome);
int retorna_index_LS(TpListaSimples *l, char *nome);
int verifica_visitado(TpListaSimples *l, char *nome);
void set_visitado(TpListaSimples *l, char *nome);
float verifica_distancia(TpListaSimples *l, char *nome);
void set_distancia(TpListaSimples *l, char *nome, float peso);
int remove_elemento_LS(TpListaSimples *l, char *nome, TpVertex *vertice);
int remove_min_LS(TpListaSimples *l, TpVertex *min);
//void imprime(lista *l
int destroi_LS(TpListaSimples *l);

#endif /* LISTA_SIMPLES_H_ */
