#include <SDL/SDL.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_ttf.h>
#include "operaGrafo.h"

//TODO editar tarefa
TpGrafo* inicializa(){
	TpGrafo* grafo;
	grafo = (TpGrafo*)malloc(sizeof(TpGrafo));

	grafo->vertices = NULL;
	grafo->numero_vertices = 0;

	return grafo;
}

void add_Tarefa_Buffer(char* buffer, TpTarefa* tarefa){
	int i;
	char auxiliar[100];

	for(int i = 0; i<sizeof(auxiliar)/sizeof(char); i++)
		auxiliar[i]= '\0';

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


void imprimeGrafo( TpGrafo* grafo){
	//for(int i = 0; i<sizeof(buffer)/sizeof(char); i++)
		//buffer[i]= '\0';
	 
	

	if(grafo->vertices == NULL){
		}else{
			
			TpVertice* aux = grafo->vertices;
			while(aux!= NULL){  // Para cada tarefa presente no grafo, adiciona ela ao buffer
				//add_Tarefa_Buffer(buffer, aux->tarefa);
				int i;
				
				
					if(aux->tarefa->tarefa_executada == 1)
						attron(COLOR_PAIR(1));
					else
						attron(COLOR_PAIR(2));
					
					printw( "%d %s %d %d %d %d", aux->tarefa->id_tarefa, aux->tarefa->nome_tarefa, aux->tarefa->tarefa_executada, 
					aux->tarefa->duracao_tarefa, aux->tarefa->inicio_min_tarefa, aux->tarefa->pre_requisitos_tarefa);

					
					for (i = 0; i < aux->tarefa->pre_requisitos_tarefa; i++){
						printw(" %d ", aux->tarefa->requisitos[i]);
					}
					printw("\n");

				aux = aux->prox;
			}
	}
}

//TODO Consistencia de tarefas;
TpGrafo* adicionaVertice(TpGrafo* grafo, TpTarefa* tarefa){
	
	TpVertice* novo = (TpVertice*)malloc(sizeof(TpVertice));
	novo->tarefa = tarefa;
	novo->tarefa->tarefa_fim = novo->tarefa->inicio_min_tarefa + novo->tarefa->duracao;
	novo->prox = NULL;

	int erro = 0;

	//2 casos

	if(grafo->vertices == NULL){//1 caso, o grafo esta vazio, entao temos que adicionar o primeiro elemento
		grafo->vertices = novo;
	
	}else{//Segundo caso, o grafo nao esta vazio, adicionamos ele ao final da lista de vertices
		TpVertice* aux = grafo->vertices;
		
		while(aux->prox != NULL){//procura o fim da lista
			if(aux->tarefa->id_tarefa == tarefa->id_tarefa){ //verifica se o elemento e inconsistente(se ja existe algum com o mesmo id)
				erro =1;
			}
			aux = aux->prox;
		}
		if(aux->tarefa->id_tarefa == tarefa->id_tarefa){														
			erro = 1;
		}

		if(!erro)
			aux->prox = novo;
	}

	grafo->numero_vertices++;
	return grafo;
}

TpGrafo* leitor(TpGrafo *grafo, char* nomeArquivo){

	FILE* file = fopen(nomeArquivo, "r+");

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


TpGrafo* removeTarefa(TpGrafo* grafo, int id){

	if(grafo->vertices != NULL){ //veridica se o grafo esta vazio
		TpVertice* aux = grafo->vertices;
		TpVertice* aux2;

		//se o grafo nao esta vazio temos 2 casos

		if(aux->tarefa->id_tarefa == id){//1- tarefa a ser removida é a primeira
			grafo->vertices = aux->prox;
			free(aux);
		
		}else{//2- tarefa a ser removida nao e a primeira
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

void salvarEmArquivo(TpGrafo* grafo, char* nomeArquivo){

	FILE* file = fopen(nomeArquivo, "w");

	if((grafo->vertices == NULL) || (file == NULL)){
	
	}else{
		for(TpVertice* aux = grafo->vertices; aux!= NULL; aux = aux->prox){
			salvaTarefa(file, aux->tarefa);
		}
	}

	fclose(file);
}

TpGrafo* ordenaTarefas (TpGrafo*){


}

int menu(){

	int opcao = 0, tecla, cima = 259, baixo = 258, enter =10;
	clear();
	
	do{
		printw("Oque deseja modificar na tarefa?  \n\n");
		printw(" [0] ID da tarefa\n");
		printw(" [1] Nome da tarefa\n");
		printw(" [2] Duracao da Tarefa\n");
		printw(" [3] Horario de inicio da Tarefa\n");
		printw(" [4] Pre requisitos da Tarefa\n");
		printw(" [5] Tarefa executada:\n");
		
		printw(" OPCAO => ");
		tecla = getch();

		clear();

	} while(tecla != enter);
	

	return opcao;
}

TpGrafo* adicionaTarefa(TpGrafo* grafo){
	TpTarefa* novo;
	novo = (TpTarefa*)malloc(sizeof(TpTarefa));
	char auxiliar[100];

	printw("Qual o novo ID?:\n ");
	scanw("%d", &novo->id_tarefa);
	printw("Qual o novo nome:\n ");
	scanw("%[^\n]", auxiliar);
	strcpy(novo->nome_tarefa, auxiliar);
	
	
	printw("Qual a duracao da tarefa:\n ");
	scanw("%d", &novo->duracao_tarefa);
	
	printw("Qual o horario de inicio da tarefa?:\n ");
	scanw("%d", &novo->inicio_min_tarefa);
	
	printw("A tarefa foi executada? \n ");
	printw("1- sim \n ");
	printw("0- nao \n ");
	scanw("%d", &novo->tarefa_executada);
	
	printw("Qual a quantidade de pre requisitos da tarefa?:\n ");
	scanw("%d", &novo->pre_requisitos_tarefa);
	
	if(novo->pre_requisitos_tarefa != 0)
		novo->requisitos = (int*)malloc(novo->pre_requisitos_tarefa*sizeof(int));

	for(int i=0; i<novo->pre_requisitos_tarefa; i++){
		printw("Qual o %d-esimo pre requisito da tarefa %s\n",i ,novo->nome_tarefa);
		scanw("%d", &novo->requisitos[i]);
	}

	printf("NUMERO%d\n", novo->inicio_min_tarefa);

	grafo = adicionaVertice(grafo, novo);
	return grafo;
}

TpGrafo* editaTarefa(TpGrafo* grafo, int id){

	if(grafo->vertices != NULL){ //veridica se o grafo esta vazio
		TpVertice* aux = grafo->vertices;
		TpVertice* aux2;
		

		//se o grafo nao esta vazio temos 2 casos

		if(aux->tarefa->id_tarefa == id){//1- tarefa a ser removida é a primeira
			
			switch(menu()){
				int auxiliar;
				char auxiliar2[100];
				case 0:
					printw("Qual o novo ID?:\n ");
					scanw("%d", &auxiliar);
					aux->tarefa->id_tarefa =auxiliar;
					break;
					
				case 1:
					printw("Qual o novo nome:\n ");
					scanw("%s", &auxiliar2);
					strcpy(aux->tarefa->nome_tarefa, auxiliar2);
					break;
					
				case 2:
					printw("Qual a nova duracao:\n ");
					scanw("%d", &auxiliar);
					aux->tarefa->duracao_tarefa = auxiliar;
					aux->tarefa->tarefa_fim = aux->tarefa->inicio_min_tarefa + aux->tarefa->duracao;

				
				case 3: 
					printw("Qual o novo horario inicio:\n ");
					scanw("%d", &auxiliar);
					aux->tarefa->inicio_min_tarefa = auxiliar;
					aux->tarefa->tarefa_fim = aux->tarefa->inicio_min_tarefa + aux->tarefa->duracao;
					break;
				

				case 5: 
					printw("Tarefa executada:\n ");
					scanw("%d", &auxiliar);
					aux->tarefa->tarefa_executada = auxiliar;
					break;

				case 4: 
					printw("Qual a quantidade de pre requisitos da tarefa?:\n ");
					scanw("%d", &auxiliar);
					aux->tarefa->pre_requisitos_tarefa = auxiliar;
			
					
					if(aux->tarefa->pre_requisitos_tarefa != 0)
						aux->tarefa->requisitos = (int*)malloc(aux->tarefa->pre_requisitos_tarefa*sizeof(int));

					for(int i=0; i<aux->tarefa->pre_requisitos_tarefa; i++){
						printw("Qual o %d-esimo pre requisito da tarefa %s\n",i ,aux->tarefa->nome_tarefa);
						scanw("%d", &aux->tarefa->requisitos[i]);
					}
					break;
					
							
			}
			return grafo;
		}else{//2- tarefa a ser removida nao e a primeira
			
			for(; aux->prox != NULL; aux = aux->prox){
				if(aux->prox->tarefa->id_tarefa == id){
					
					switch(menu()){
						
						int auxiliar;
						char auxiliar2[100];
						case 0:
							printw("Qual o novo ID?:\n ");
							scanw("%d", &auxiliar);
							aux->tarefa->id_tarefa =auxiliar;
							break;
						case 1:
							printw("Qual o novo nome:\n ");
							scanw("%s", auxiliar2);
							strcpy(aux->tarefa->nome_tarefa, auxiliar2);			
							break;
						case 2:
							printw("Qual a duracao da tarefa:\n ");
							scanw("%d", &auxiliar);
							aux->tarefa->duracao_tarefa = auxiliar;
							aux->tarefa->tarefa_fim = aux->tarefa->inicio_min_tarefa + aux->tarefa->duracao;
							break;
						case 3: 
							printw("Qual o novo horario inicio:\n ");
							scanw("%d", &auxiliar);
							aux->tarefa->inicio_min_tarefa = auxiliar;
							aux->tarefa->tarefa_fim = aux->tarefa->inicio_min_tarefa + aux->tarefa->duracao;
							break;

						case 5: 
							printw("Tarefa executada:\n ");
							scanw("%d", &auxiliar);
							aux->tarefa->tarefa_executada = auxiliar;
							break;
						case 4: 
							printw("Qual a quantidade de pre requisitos da tarefa?:\n ");
							scanw("%d", &auxiliar);
							aux->tarefa->pre_requisitos_tarefa = auxiliar;
							
							if(aux->tarefa->pre_requisitos_tarefa != 0)
								aux->tarefa->requisitos = (int*)malloc(aux->tarefa->pre_requisitos_tarefa*sizeof(int));

							for(int i=0; i<aux->tarefa->pre_requisitos_tarefa; i++){
								printw("Qual o %d-esimo pre requisito da tarefa %s\n",i ,aux->tarefa->nome_tarefa);
								scanw("%d", &aux->tarefa->requisitos[i]);
							}
							break;
							
					}//switch
					
					return grafo;
				}//if
			}//for
			
		}//else
	}//if maior
}//funcao

