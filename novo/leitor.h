


struct Tarefa{
	int id_tarefa;
	char nome_tarefa[100];
	int tarefa_executada;
	int duracao_tarefa;
	int inicio_min_tarefa;
	int pre_requisitos_tarefa;
	int *requisitos;
	//int visitado;
	//int id;
};

typedef struct Tarefa TpTarefa;

struct vertice{
	TpTarefa* tarefa;
	struct vertice *prox;
};


typedef struct vertice TpVertice;

struct Grafo {
	TpVertice* vertices;
	//TpListaDupla *adjacencia;
	int numero_vertices;
	//int numero_origens;
	int tam_vetor_lista;	
};



typedef struct Grafo TpGrafo;



TpGrafo* inicializa(void);
TpGrafo* adicionaVertice(TpGrafo*, TpTarefa* );
TpGrafo* leitor(TpGrafo *);
//void imprimeTarefa(TpTarefa* );
//void imprimeGrafo(TpGrafo* );
TpGrafo* removeTarefa(TpGrafo* , int );
void salvaTarefa(FILE* , TpTarefa* );
void salvarEmArquivo(TpGrafo* );