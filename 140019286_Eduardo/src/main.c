#include <stdio.h>
#include <stdlib.h>
#include <grafo.h>
#include <assert.h>

int main() {
	enum Options {INSERE_VERTEX = 1, REMOVE_VERTEX = 2, INSERE_ARESTA = 3, REMOVE_ARESTA = 4,
				  CALCULA_DISTANCIA = 5, GRAFO_CONEXO = 6, GRAFO_CONSISTENTE = 7};

	char answer, origem[TAM_MAX], destino[TAM_MAX];
	char input_name[TAM_MAX], output_name[TAM_MAX];
	int option, type;
	float peso;
	FILE *input = NULL, *output = NULL;
	TpGrafo grafo;
	TpVertex vertex1;
	
	printf("Digite o nome do arquivo de entrada:\n");
	scanf("%[^\n]", input_name);
	getchar();
	input = fopen(input_name, "r");

	printf("Digite o nome do arquivo de saida:\n");
	scanf("%[^\n]", output_name);
	getchar();
	output = fopen(output_name, "w");

	assert(input != NULL && output != NULL);	

	le_grafo(input, &grafo);

	printf("\nPrograma para realizar operacoes sobre um grafo.\n\n");

	printf("Digite a operacao que deseja realizar:\n");
	printf("[1] Insere vertice.\n");
	printf("[2] Remove vertice.\n");
	printf("[3] Insere aresta.\n");
	printf("[4] Remove aresta.\n");
	printf("[5] Calcula distancia.\n");
	printf("[6] Verifica se o grafo e conexo.\n");
	printf("[7] Verifica se o grafo e consistente.\n");
	printf("[8] Sai da aplicacao.\n");
	scanf("%d", &option);
	getchar();
	while(option < 1 || option > 8) {
		printf("Valor invalido. Tente novamente.\n");
		printf("[1] Insere vertice.\n");	
		printf("[2] Remove vertice.\n");
		printf("[3] Insere aresta.\n");
		printf("[4] Remove aresta.\n");
		printf("[5] Calcula distancia.\n");
		printf("[6] Verifica se o grafo e conexo.\n");
		printf("[7] Verifica se o grafo e consistente.\n");
		printf("[8] Sai da aplicacao.\n");
		scanf("%d", &option);
		getchar();
	}

	while(option != 8) {
		switch (option) {
			case INSERE_VERTEX:
				printf("Digite o nome do vertice que sera inserido:\n");
				fgets(vertex1.nome, TAM_MAX, stdin);
				vertex1.id = grafo.numero_vertices;
				printf("O vertice e origem [s/n]?\n");
				scanf("%c", &answer);
				while(answer != 's' && answer != 'n') {
					printf("Resposta invalida. Tente novamente.\n");
					printf("O vertice e origem [s/n]?\n");
					scanf("%c", &answer);
				}
				answer == 's'? type = ORIGEM: type = NAO_ORIGEM;
				insere_vertex(&grafo, vertex1, type);
				break;
			case REMOVE_VERTEX:
				printf("Deseja proceder com a operacao [s/n]? O grafo pode se tornar inconsistente.\n");
				while(answer != 's' && answer != 'n') {
					printf("Resposta invalida. Tente novamente.\n");
					printf("Deseja proceder com a operacao [s/n]? O grafo pode se tornar inconsistente.\n");
					scanf("%c", &answer);
				}
				if(answer == 'n') {
					break;
				} 
				printf("Digite o nome do vertice que sera retirado:\n");
				fgets(vertex1.nome, TAM_MAX, stdin);
				remove_vertex(&grafo, &vertex1, vertex1.nome);
				break;
			case INSERE_ARESTA:
				printf("Digite o nome da origem da aresta que sera criada:\n");
				fgets(origem, TAM_MAX, stdin);
				printf("Digite o nome do destino da aresta que sera criada:\n");
				fgets(destino, TAM_MAX, stdin);
				printf("Digite o peso entre os vertices:n");
				scanf("%f", &peso);
				insere_aresta(&grafo, origem, destino, peso);
				break;
			case REMOVE_ARESTA:
				printf("Digite o nome da origem da aresta que sera retirada:\n");
				fgets(origem, TAM_MAX, stdin);
				printf("Digite o nome do destino da aresta que sera retirada:\n");
				fgets(destino, TAM_MAX, stdin);
				remove_aresta(&grafo, origem, destino);
				break;
			case CALCULA_DISTANCIA:
				printf("Digite o nome da origem para o calculo da distancia:\n");
				fgets(origem, TAM_MAX, stdin);
				printf("Digite o nome do destino para o calculo da distancia:\n");
				fgets(destino, TAM_MAX, stdin);
				calculaDistancia(&grafo, origem, destino);
				break;
			case GRAFO_CONEXO:
				grafoConexo(&grafo) == EXIT_SUCCESS? printf("O grafo e conexo.\n"): printf("O grafo nao e conexo.\n");
				break;
			case GRAFO_CONSISTENTE:
				grafoConsistente(&grafo) == EXIT_SUCCESS? printf("O grafo e consistente.\n"): printf("O grafo nao e consistente.\n");
				break;
			default:
				printf("ERRO!\n");
		}

		printf("Digite a operacao que deseja realizar:\n");
		printf("[1] Insere vertice.\n");
		printf("[2] Remove vertice.\n");
		printf("[3] Insere aresta.\n");
		printf("[4] Remove aresta.\n");
		printf("[5] Calcula distancia.\n");
		printf("[6] Verifica se o grafo e conexo.\n");
		printf("[7] Verifica se o grafo e consistente.\n");
		printf("[8] Sai da aplicacao.\n");
		scanf("%d", &option);
		getchar();
		while(option < 1 || option > 8) {
			printf("Valor invalido. Tente novamente.\n");
			printf("[1] Insere vertice.\n");
			printf("[2] Remove vertice.\n");
			printf("[3] Insere aresta.\n");
			printf("[4] Remove aresta.\n");
			printf("[5] Calcula distancia.\n");
			printf("[6] Verifica se o grafo e conexo.\n");
			printf("[7] Verifica se o grafo e consistente.\n");
			printf("[8] Sai da aplicacao.\n");
			scanf("%d", &option);
			getchar();
		}

	}

	escreve_grafo(output, &grafo);

	destroi_grafo(&grafo);

	printf("Fim da execucao da aplicacao.\n");
	printf("Pressione a tecla 'enter' para encerrar.\n");
	getchar();
	
	return 0;
}
