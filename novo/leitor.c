#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Tarefa{
	int id_tarefa;
	char nome_tarefa[100];
	int tarefa_executada;
	int duracao_tarefa;
	int inicio_min_tarefa;
	int pre_requisitos_tarefa;
	int *requisitos;
	//int visitado;
	//int id;
}TpTarefa;

typedef struct vertice
{
	TpTarefa* tarefa;
	struct vertice *prox;
}TpVertice;

typedef struct Grafo {
	TpVertice* vertices;
	//TpListaDupla *adjacencia;
	int numero_vertices;
	//int numero_origens;
	int tam_vetor_lista;	
}TpGrafo;

//TODO editar tarefa

TpGrafo* inicializa();
TpGrafo* adicionaVertice(TpGrafo* grafo, TpTarefa* tarefa);
TpGrafo* leitor(TpGrafo *grafo);
void imprimeTarefa(TpTarefa* tarefa);
void imprimeGrafo(TpGrafo* grafo);
TpGrafo* removeTarefa(TpGrafo* grafo, int id);
void salvaTarefa(FILE* file, TpTarefa* tarefa);
void salvarEmArquivo(TpGrafo* Grafo);

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

TpGrafo* adicionaVertice(TpGrafo* grafo, TpTarefa* tarefa){
	
	TpVertice* novo = (TpVertice*)malloc(sizeof(TpVertice));
	novo->tarefa = tarefa;

	

	if(grafo->vertices == NULL){
		grafo->vertices = novo;
	}else{
		TpVertice* aux = grafo->vertices;
		
		while(aux->prox != NULL)
			aux = aux->prox;

		aux->prox = novo;

	}

	grafo->numero_vertices++;
	grafo->tam_vetor_lista++;
	/*if(tarefa.pre_requisitos_tarefa == 0) grafo.numero_origens++;*/

	return grafo;
}

/**
	TODO mudar o dado da estrutura grafo para ser um TpTarefa
*/
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

void imprimeTarefa(TpTarefa* tarefa){
	printf("%d '%s' %d %d %d %d", tarefa->id_tarefa, tarefa->nome_tarefa, tarefa->tarefa_executada, tarefa->duracao_tarefa,
									tarefa->inicio_min_tarefa, tarefa->pre_requisitos_tarefa);
	for (int i = 0; i < tarefa->pre_requisitos_tarefa; ++i){
		printf(" %d", tarefa->requisitos[i]);
	}
	printf("\n");

}

void imprimeGrafo(TpGrafo* grafo){
	/* Funçao provisoria, arrumar depois*/

	if(grafo->vertices == NULL){
	}else{
		TpVertice* aux = grafo->vertices;
		while(aux!= NULL){	
			imprimeTarefa(aux->tarefa);
			aux = aux->prox;
		}
	}
}

//TODO pode ser feito uma forma de identificar se a tarefa foi excluida.
TpGrafo* removeTarefa(TpGrafo* grafo, int id){

	if(grafo->vertices != NULL){
		TpVertice* aux = grafo->vertices;

		if(aux->tarefa->id_tarefa == id){//tarefa a ser removida é a primeira
			grafo->vertices = aux->prox;
			free(aux);
		}else{
			for(aux = grafo->vertices; aux->prox != NULL; aux = aux->prox){
				if(aux->prox->tarefa->id_tarefa == id){
					aux->prox = aux->prox->prox;
					free(aux->prox);
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

	FILE* file = fopen("trf2", "w");

	if((grafo->vertices == NULL) || (file == NULL)){
	
	}else{
		for(TpVertice* aux = grafo->vertices; aux!= NULL; aux = aux->prox){
			salvaTarefa(file, aux->tarefa);
		}
	}

	fclose(file);
}


