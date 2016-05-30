/*
 * Módulo: lista.h;
 *
 * Estudante: Eduardo Henrique Costa Moresi;
 * Matrícula: 14/0019286;
 *
 * Data: 27/04/2016;
 */

#ifndef LISTA_DUPLA_H_
#define LISTA_DUPLA_H_

#include <lista_simples.h> /* A lista duplamente encadeada faz uso do tipo vertex definido nesse módulo; */

typedef struct Info {
	TpVertex origem;
	TpVertex destino;
	float peso;
}TpInfo;

typedef struct Cell {
	TpInfo key;
	struct Cell *proxima;
	struct Cell *anterior;
}TpCelula;

typedef struct List {
	int tamanho;
	TpCelula *inicio;
	TpCelula *fim;
}TpListaDupla;

int cria_LD(TpListaDupla *lista);
int insere_LD(TpListaDupla *lista, TpInfo info);
int checa_vazia_LD(TpListaDupla *lista);
int procura_chave_LD(TpListaDupla *lista, int id);
int remove_elemento_LD(TpListaDupla *Lista, TpInfo *elemento, int index);
int destroi_LD(TpListaDupla *lista);

#endif /* LISTA_DUPLA_H_ */
