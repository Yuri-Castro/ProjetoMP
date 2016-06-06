#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <grafo.h>

typedef struct Tarefa{
	int id_tarefa;
	char nome_tarefa[100];
	int tarefa_executada;
	int duracao_tarefa;
	int inicio_min_tarefa;
	int pre_requisitos_tarefa;
	int *requisitos;
}TpTarefa;



/**
	TODO mudar o dado da estrutura grafo para ser um TpTarefa
*/
TpGrafo* leitor(TpGrafo *grafo, FILE* file){

	TpTarefa* nova;
	nova = (TpTarefa*)malloc(sizeof(TpTarefa));

	do{
		fscanf(file,"%d", &nova->id_tarefa);
		fgetc(file);
		if(fgetc(file) != '\''){
			fgetc(file);
			fgetc(file);
		}
		fscanf(file,"%[^'’‘\n]", nova->nome_tarefa);
		if(fgetc(file) != '\''){
			fgetc(file);
			fgetc(file);
		}
		fgetc(file);
		fscanf(file,"%d", &nova->tarefa_executada);
		fgetc(file);
		fscanf(file,"%d", &nova->duracao_tarefa);
		fgetc(file);
		fscanf(file,"%d", &nova->inicio_min_tarefa);
		fgetc(file);
		fscanf(file,"%d", &nova->pre_requisitos_tarefa);

		if(nova->pre_requisitos_tarefa != 0)
			nova->requisitos = (int*)malloc(nova->pre_requisitos_tarefa*sizeof(int));

		for(int i=0; i<nova->pre_requisitos_tarefa; i++){
			fgetc(file);
			fscanf(file, "%d", &nova->requisitos[i]);
		}

		if(feof(file)) break;

		fgetc(file);

	}while(!foef());

}