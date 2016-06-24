/*
 * Módulo: lista.cpp;
 *
 * Estudante: Eduardo Henrique Costa Moresi;
 * Matrícula: 14/0019286;
 *
 * Data: 27/04/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <lista_dupla.h>

/* Cria uma lista vazia; */
int cria_LD(TpListaDupla *lista) {
	lista->inicio = (TpCelula *)malloc(sizeof(TpCelula));
	if(lista->inicio == NULL) {
		perror("ERROR");
		return (EXIT_FAILURE);
	}
	lista->inicio->anterior = NULL;
	lista->inicio->proxima = NULL;
	lista->fim = lista->inicio;
	lista->tamanho = 0;

	return (EXIT_SUCCESS);
}

/* Insere um elemento na lista; */
int insere_LD(TpListaDupla *lista, TpInfo info) { /* Elemento é inserido no início da lista; */
	TpCelula *aux;
	aux = (TpCelula *)malloc(sizeof(TpCelula));
	if(aux == NULL) {
		perror("ERROR");
		return (EXIT_FAILURE);
	}
	
	aux->key = info;

	if(checa_vazia_LD(lista)) {
		aux->proxima = NULL;
		aux->anterior = lista->inicio;
		lista->inicio->proxima = aux;
		lista->fim = aux;		
	}
	else {
		aux->anterior = lista->inicio;
		aux->proxima = lista->inicio->proxima;
		lista->inicio->proxima->anterior = aux;
		lista->inicio->proxima = aux;	
	}
	lista->tamanho++;
	return (EXIT_SUCCESS);
}

int checa_vazia_LD(TpListaDupla *lista) {
	return (lista->inicio == lista->fim);
}

/* Procura um elemento a partir do seu identificador; */
int procura_chave_LD(TpListaDupla *lista, int id) { /* Recebe o 'id' e retorna o index; */
	if(checa_vazia_LD(lista)) {
		return (ERRO);
	}
	
	int index;
	TpCelula *aux;

	index = 0;
	aux = lista->inicio->proxima;
	while((aux != NULL) && (aux->key.destino.id != id)) {
		aux = aux->proxima;
		index++;
	}

	if(!aux) {
		return (ERRO);
	}

	return index;
}

/* Função que remove um dado elemento de acordo com o seu index; */
int remove_elemento_LD(TpListaDupla *lista, TpInfo *elemento, int index) {
	int i = 0;
	TpCelula *aux = lista->inicio->proxima;

	if(checa_vazia_LD(lista)) {
		return (EXIT_FAILURE);
	}

	while(i < index) {
		aux = aux->proxima;
		i++;
	}

	if(!aux) {
		return (EXIT_FAILURE);
	}
	else if(aux == lista->inicio->proxima) {
		if(aux->proxima != NULL) {
			aux->proxima->anterior = lista->inicio;
			lista->inicio->proxima = aux->proxima;	
		}
		else {
			lista->inicio->proxima = NULL;
		}
	}
	else if(aux == lista->fim) {
		aux->anterior->proxima = NULL;
		lista->fim = aux->anterior;
	}
	else {
		aux->anterior->proxima = aux->proxima;
		aux->proxima->anterior = aux->anterior;

	}

	*elemento = aux->key;
	free(aux);
	lista->tamanho--;

	return (EXIT_SUCCESS);	
}

/* Função que libera toda a memória em uso pela lista; */
int destroi_LD(TpListaDupla *lista) {
	if(checa_vazia_LD(lista)) {
		free(lista->inicio);
		return (EXIT_SUCCESS);
	}
	
	TpCelula *aux, *dead;
	aux = lista->inicio;	

	while(aux != NULL) {
		dead = aux;
		aux = aux->proxima;
		free(dead);
	}
	lista->tamanho = 0;
	return (EXIT_SUCCESS);
}


