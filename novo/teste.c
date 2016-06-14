#include <stdlib.h>
#include <stdio.h>
#include "leitor.h"


int main(){

	TpGrafo* grafo;
	grafo = inicializa();
	
	grafo = leitor(grafo);

	imprimeGrafo(grafo);

	salvarEmArquivo(grafo);
	
}