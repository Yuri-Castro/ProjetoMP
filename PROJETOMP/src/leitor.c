#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_ttf.h>
#include "leitor.h"

//TODO editar tarefa

TpGrafo* inicializa(){
	TpGrafo* grafo;
	grafo = (TpGrafo*)malloc(sizeof(TpGrafo));

	grafo->vertices = NULL;
	//grafo->adjacencia = NULL;
	grafo->numero_vertices = 0;
	//grafo.numero_origens = 0;
	grafo->tam_vetor_lista = 0;

	return grafo;
}

void add_Tarefa_Buffer(char* buffer, TpTarefa* tarefa){
	int i;
	char auxiliar[100];

	sprintf(auxiliar, "%d %s %d %d %d %d", tarefa->id_tarefa, tarefa->nome_tarefa, tarefa->tarefa_executada, 
	tarefa->duracao_tarefa, tarefa->inicio_min_tarefa, tarefa->pre_requisitos_tarefa);

	strcat(buffer, auxiliar);

	for (i = 0; i < tarefa->pre_requisitos_tarefa; i++){

		sprintf(auxiliar, " %d", tarefa->requisitos[i]);
		strcat(buffer, auxiliar);
	}

	sprintf(auxiliar, "\n");
	strcat(buffer, auxiliar);
}


void imprimeGrafo(char* buffer, TpGrafo* grafo){

	if(grafo->vertices == NULL){
		}else{
			TpVertice* aux = grafo->vertices;
			while(aux!= NULL){  
			add_Tarefa_Buffer(buffer, aux->tarefa);
			aux = aux->prox;
		}
	}
}

//TODO Consistencia de tarefas;
TpGrafo* adicionaVertice(TpGrafo* grafo, TpTarefa* tarefa){
	
	TpVertice* novo = (TpVertice*)malloc(sizeof(TpVertice));
	novo->tarefa = tarefa;

	if(grafo->vertices == NULL){
		grafo->vertices = novo;
	
	}else{
		TpVertice* aux = grafo->vertices;
		
		while(aux->prox != NULL){
			if(aux->tarefa->id_tarefa == tarefa->id_tarefa){
				printf("impossivel adicionar %sm id repetido\n", tarefa->nome_tarefa);
				return grafo;
			}
			aux = aux->prox;
		}
		if(aux->tarefa->id_tarefa == tarefa->id_tarefa){
			printf("impossivel adicionar %s, id repetido\n", tarefa->nome_tarefa);
			return grafo;
		}

		aux->prox = novo;
	}

	grafo->numero_vertices++;
	grafo->tam_vetor_lista++;

	return grafo;
}

TpGrafo* leitor(TpGrafo *grafo){

	FILE* file = fopen("tarefas", "r+");

	while(1){
		TpTarefa* novo;
		novo = (TpTarefa*)malloc(sizeof(TpTarefa));

		fscanf(file,"%d", &novo->id_tarefa);
		if (feof(file)) break;

		fgetc(file);
		if(fgetc(file) != '\''){
			fgetc(file);
			fgetc(file);
		}
		fscanf(file,"%[^'’‘\n]", novo->nome_tarefa);
		if(fgetc(file) != '\''){
			fgetc(file);
			fgetc(file);
		}
		fgetc(file);
		fscanf(file,"%d", &novo->tarefa_executada);
		fgetc(file);
		fscanf(file,"%d", &novo->duracao_tarefa);
		fgetc(file);
		fscanf(file,"%d", &novo->inicio_min_tarefa);
		fgetc(file);
		fscanf(file,"%d", &novo->pre_requisitos_tarefa);

		if(novo->pre_requisitos_tarefa != 0)
			novo->requisitos = (int*)malloc(novo->pre_requisitos_tarefa*sizeof(int));

		for(int i=0; i<novo->pre_requisitos_tarefa; i++){
			fgetc(file);
			fscanf(file, "%d", &novo->requisitos[i]);
		}

		grafo = adicionaVertice(grafo, novo);
	}

	fclose(file);

	return grafo;

}

//TODO pode ser feito uma forma de identificar se a tarefa foi excluida.
TpGrafo* removeTarefa(TpGrafo* grafo, int id){

	if(grafo->vertices != NULL){
		TpVertice* aux = grafo->vertices;
		TpVertice* aux2;

		if(aux->tarefa->id_tarefa == id){//tarefa a ser removida é a primeira
			grafo->vertices = aux->prox;
			free(aux);
		
		}else{
			for(; aux->prox != NULL; aux = aux->prox){
				if(aux->prox->tarefa->id_tarefa == id){
					aux2 = aux->prox;
					aux->prox = aux->prox->prox;
					free(aux2);
					break;
				}
			}
		}
	}
	return grafo;
}

void salvaTarefa(FILE* file, TpTarefa* tarefa){
	fprintf(file, "%d '%s' %d %d %d %d", tarefa->id_tarefa, tarefa->nome_tarefa, tarefa->tarefa_executada, tarefa->duracao_tarefa,
									tarefa->inicio_min_tarefa, tarefa->pre_requisitos_tarefa);
	for (int i = 0; i < tarefa->pre_requisitos_tarefa; ++i){
		fprintf(file, " %d", tarefa->requisitos[i]);
	}
	fprintf(file, "\n");	
}

void salvarEmArquivo(TpGrafo* grafo){

	FILE* file = fopen("tarefas", "w");

	if((grafo->vertices == NULL) || (file == NULL)){
	
	}else{
		for(TpVertice* aux = grafo->vertices; aux!= NULL; aux = aux->prox){
			salvaTarefa(file, aux->tarefa);
		}
	}

	fclose(file);
}