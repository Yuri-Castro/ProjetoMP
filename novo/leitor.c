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

TpGrafo* inicializa(TpGrafo* grafo);
TpGrafo* adicionaVertice(TpGrafo* grafo, TpTarefa* tarefa);
TpGrafo* leitor(TpGrafo *grafo, FILE* file);
void imprimeTarefa(TpTarefa* tarefa);
void imprimeGrafo(TpGrafo* grafo);

TpGrafo* inicializa(TpGrafo* grafo){
	grafo->vertices = NULL;
	//grafo->adjacencia = NULL;
	grafo->numero_vertices = 0;
	//grafo.numero_origens = 0;
	grafo->tam_vetor_lista = 0;
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
TpGrafo* leitor(TpGrafo *grafo, FILE* file){
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

/*TODO
	Modularizar o codigo.
	Ajustar o makefile para ser mais flexivel
	Funçoes para adicionar tarefa(no arquivo e no grafo)
	Funçoes para remover tarefa(do arquivo e do grafo)
	Funçoes para editar tarefas(no arquivo e no grafo)
	Verificador de coezao.
	Fazer textes usando gteste

*/


int main(){
	TpGrafo* grafo;
	grafo = (TpGrafo*)malloc(sizeof(TpGrafo));
	FILE* file = fopen("tarefas", "r+");
	grafo = inicializa(grafo);
	grafo = leitor(grafo, file);
	imprimeGrafo(grafo);
	fclose(file);
}