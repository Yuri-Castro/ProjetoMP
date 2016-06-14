
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