#include <SDL/SDL.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_ttf.h>
#include "operaGrafo.h"

//TODO editar tarefa


int menu(){
	

	int opcao = 0, tecla, cima = 259, baixo = 258, enter =10;
		
	
	clear();
	
	do{
		
		

		printw("Oque deseja modificar na tarefa?  \n");
		(opcao == 0) ? printw("->") : printw("  ");
		printw(" ID da tarefa\n");
		(opcao == 1) ? printw("->") : printw("  ");
		printw(" Nome da tarefa\n");
		(opcao == 2) ? printw("->") : printw("  ");
		printw(" Duracao da Tarefa\n");
		(opcao == 3) ? printw("->") : printw("  ");
		printw(" Horario de inicio da Tarefa\n");
		(opcao == 4) ? printw("->") : printw("  ");
		printw(" Pre requisitos da Tarefa\n");
		
		
		tecla = getch();
	
		
		if(tecla == baixo)
			(opcao == 4) ? opcao = 0: opcao++;
		if(tecla == cima)
			(opcao == 0) ? opcao = 4: opcao--;
		
		clear();

	} while(tecla != enter);
	

	return opcao;
}

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
			while(aux!= NULL){  // Para cada tarefa presente no grafo, adiciona ela ao buffer
			add_Tarefa_Buffer(buffer, aux->tarefa);
			aux = aux->prox;
		}
	}
}

//TODO Consistencia de tarefas;
TpGrafo* adicionaVertice(TpGrafo* grafo, TpTarefa* tarefa){
	
	TpVertice* novo = (TpVertice*)malloc(sizeof(TpVertice));
	novo->tarefa = tarefa;

	//2 casos

	if(grafo->vertices == NULL){//1 caso, o grafo esta vazio, entao temos que adicionar o primeiro elemento
		grafo->vertices = novo;
	
	}else{//Segundo caso, o grafo nao esta vazio, adicionamos ele ao final da lista de vertices
		TpVertice* aux = grafo->vertices;
		
		while(aux->prox != NULL){//procura o fim da lista
			if(aux->tarefa->id_tarefa == tarefa->id_tarefa){ //verifica se o elemento e inconsistente(se ja existe algum com o mesmo id)
				return grafo;
			}
			aux = aux->prox;
		}
		if(aux->tarefa->id_tarefa == tarefa->id_tarefa){														
			return grafo;
		}

		aux->prox = novo;
	}

	grafo->numero_vertices++;
	return grafo;
}
TpGrafo* adicionaTarefa(TpGrafo* grafo){
	TpTarefa* novo;
	char auxiliar[100];

	printw("Qual o novo ID?:\n ");
	scanw("%d", &novo->id_tarefa);
	printf("teste");
	printw("Qual o novo nome:\n ");
	scanw("%d", &auxiliar);
	strcpy(novo->nome_tarefa, auxiliar);
	
	
	printw("Qual a duracao da tarefa:\n ");
	scanw("%d", &novo->duracao_tarefa);
	
	printw("Qual o horario de inicio da tarefa?:\n ");
	scanw("%d", &novo->inicio_min_tarefa);
	
	printw("A tarefa foi executada? 1/0:\n ");
	scanw("%d", &novo->tarefa_executada);
	
	printw("Qual a quantidade de pre requisitos da tarefa?:\n ");
	scanw("%d", &novo->pre_requisitos_tarefa);
	

	

	if(novo->pre_requisitos_tarefa != 0)
		novo->requisitos = (int*)malloc(novo->pre_requisitos_tarefa*sizeof(int));

	for(int i=0; i<novo->pre_requisitos_tarefa; i++){
		printw("Qual o %d-esimo pre requisito da tarefa %s\n",i ,novo->nome_tarefa);
		scanw("%d", &novo->requisitos[i]);
	}

	grafo = adicionaVertice(grafo, novo);
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
					printw("Qual o  novo inicio da tarefa:\n ");
					scanw("%d", &auxiliar);
						aux->tarefa->duracao_tarefa = auxiliar;
				
				case 3: 
					printw("Qual o novo pre requisito da tarefa?:\n ");
					scanw("%d", &auxiliar);
					aux->tarefa->pre_requisitos_tarefa = auxiliar;
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
							break;
						case 3: 
							printw("Qual o horario de inicio da tarefa?:\n ");
							scanw("%d", &auxiliar);
							aux->tarefa->pre_requisitos_tarefa = auxiliar;
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

