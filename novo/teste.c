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
}TpTarefa;



/**
	TODO mudar o dado da estrutura grafo para ser um TpTarefa
*/

/*
TpTarefa** leitor( FILE* file){

	TpTarefa** tarefas;
	tarefas=(TpTarefa**)malloc(10*sizeof(TpTarefa*));
	int count = 0;

	{	TpTarefa* nova;
		nova = (TpTarefa*)malloc(sizeof(TpTarefa));
		printf("1\n");


		while(fscanf(file, "%d '%[^']' %d %d %d %d", &nova->id_tarefa, nova->nome_tarefa, &nova->tarefa_executada,
													&nova->duracao_tarefa, &nova->inicio_min_tarefa, &nova->pre_requisitos_tarefa ) >= 2){
			printf("2\n");

			if(nova->pre_requisitos_tarefa != 0)
				nova->requisitos = (int*)malloc(nova->pre_requisitos_tarefa*sizeof(int));

			for(int i=0; i<nova->pre_requisitos_tarefa; i++){
				fscanf(file, " %d", &nova->requisitos[i]);
			}
			fgetc(file);
		}
		printf("3\n");

		tarefas[count] = nova;
		count ++;

	}

	return tarefas;
}

*/
int main(){


	TpTarefa* nova;
	nova = (TpTarefa*)malloc(sizeof(TpTarefa));
	
	FILE* file;
	file = fopen("entrada", "r");


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

	printf("%s\n",nova->nome_tarefa);
	printf("%d\n", nova->duracao_tarefa);

}