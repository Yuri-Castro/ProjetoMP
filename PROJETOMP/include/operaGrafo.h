/**
	Struct Tarefa: Para armazenar os dados de uma tarefa

	@param: id_tarefa = identificador da tarefa
	@param: nome_tarefa = nome da tarefa
	@param: tarefa_executada = bool, 1 se a tarefa ja foi executado, o caso contrario
	@param: duracao_tarefa = tempo necessario para completar a tarefa
	@param: inicio_min = indica o tempo minimo para que a tarefa precisa esperar antes de começar
	@param: pre_requisitos_tarefa = indica a quantidade de pre requisitos para a tarefa dada
	@param: requisitos = vetor contendo o identificador de todas as tarefas que precisam ser executadas antes dessa tarefa
*/
struct Tarefa{
	int id_tarefa;
	char nome_tarefa[100];
	int tarefa_executada;
	int duracao_tarefa;
	int inicio_min_tarefa;
	int pre_requisitos_tarefa;
	int *requisitos;
};
typedef struct Tarefa TpTarefa;


/**
	Struct vertice: Vertice de uma lista encadeada

	@param: tarefa = conteudo do vertice, no caso uma tarefa
	@param: prox = ponteiro que ira indicar o prox vertice da lista tarefas que precisam ser executadas antes dessa tarefa
*/
struct vertice{
	TpTarefa* tarefa;
	struct vertice *prox;
};
typedef struct vertice TpVertice;



/**
	Struct Grafo: cabeça da estrutura de dados do grafo

	@param: vertices = lista dos vertices que compõe o grafo
	@param: numero_vertices = quantidade atual de vertices contida no grafo

*/
struct Grafo {
	TpVertice* vertices;
	int numero_vertices;
};
typedef struct Grafo TpGrafo;


/***************************************************************************
*Função: 
*	inicializa
*
*Descrição
*	Inicializa um ponteiro para um tipo grafo.
*	Aloca memoria
*	Definine as constantes inicias.
*
*Parâmetros
*	void
*
*Valor retornado
*	Retorna um TpGrafo* caso a alocação seja bem sucedida, NULL caso contrario
*
*Assertiva de entrada
*	void
*
*Assertiva de saída
* O ponteiro retornado tem os atributos:
*	vertices = NULL;
*	numero_vertices = 0
*	tam_vetor_lista = 0
**************************************************************************/
TpGrafo* inicializa();

/***************************************************************************
*Função: 
*	adicionaVertice
*
*Descrição
*	Adiciona uma uma tarefa à lista de tarefas atual
*	A tarefa e sempre adicionada no final da lista
*	Caso a tarefa tenha um identificador já existente ela não é adicionada
*
*Parâmetros
*	TpGrafo* = grafo no qual deve ser inserido o vertice
*	TpTarefa* = Conteudo do vertice a ser inserido
*	
*Valor retornado
*	Retorna o grafo com o vertice adicionado, caso a inserção seja bem sucedida 
*	Retorna o mesmo grafo passado caso a inserção tenha falhado
*
*Assertiva de entrada
*	TpTarefa* != NULL
*
*Assertiva de saída
*	numero de vertices do grafo e incrementado
*	tamanho do vetor lista e incrementado
*	o conteudo do ultimo elemento do grafo é a tarefa passada
*	O grafo permanece conexo
**************************************************************************/
TpGrafo* adicionaVertice(TpGrafo*, TpTarefa* );

/***************************************************************************
*Função: 
*	leitor
*
*Descrição
*	Função abre um arquivo chamado "tarefas", le todas as tarefas do arquivo e coloca em memoria
		OBS: 	As tarefas tem que estar oredenadas da seguinte forma
		id "nome" foi_executada duraçao inicio qt_pre_requisitos pre_requisitos ex:
		102 'terceira tarefa' 0 2 3 2 100 101

*
*Parâmetros
*	TpGrafo* = grafo no qual serão salvas as tarefas lidas
*	char *, nome do arquivo a ser lido
*	
*Valor retornado
*	Retorna o grafo com todas as tarefas contidas no arquivo
*
*Assertiva de entrada
*	TpGrafo != NULL
*
*Assertiva de saída
*	para cada tarefa consistente no arquivo, sera gerado um vertice no grafo
**************************************************************************/
TpGrafo* leitor(TpGrafo *, char *);

/***************************************************************************
*Função: 
*	imprimeTarefa
*
*Descrição
*	Le uma tarefa e salva o conteudo em uma string, em suma é uma funçao para auxiliar a impressão do grafo.
*
*Parâmetros
*	TpGrafo* = grafo so qual serão lidas as tarefas
*	char* = String no qual sera armazenado o conteudo da tarefa
*	
*Valor retornado
*	void
*
*Assertiva de entrada
*	TpGrafo* != NULL
*	char* != NULL
*
*Assertiva de saída
*	o conteudo da tarefa passada sera salvo na string
**************************************************************************/
void imprimeTarefa(char* ,TpTarefa* );

/***************************************************************************
*Função: 
*	imprimeGrafo
*
*Descrição
*	Le todas as tarefas de um grafo para uma string
*
*Parâmetros
*	TpGrafo* = grafo do qual serão lidos os vertices
*	char* = string no qual serao armazenados os valores lidos
*	
*Valor retornado
*	void
*
*Assertiva de entrada
*	TpGrafo* != NULL
*	char* != NULL
*
*Assertiva de saída
*	O grafo permanecera inalterado
*	o char* contera todos os dados do grafo
**************************************************************************/
void imprimeGrafo(char* , TpGrafo* );

/***************************************************************************
*Função: 
*	removeTarefa
*
*Descrição
*	Recebe um int (identificador) e remove a tarefa do grafo que esta relacionada a esse identificador
*
*Parâmetros
*	TpGrafo* = grafo do qual sera excluido a tarefa
*	int = identificador da tarefa a ser removida
*	
*Valor retornado
*	Caso exista um vertice com o identificador passado, retorna o grafo sem aquele vertice
*	Caso não exista um vertice com o identificador passado, retorna o grafo inalterado
*
*Assertiva de entrada
*	int > 0
*	TpGrafo != NULL
*
*Assertiva de saída
*	a tarefa com o identificador passado e removida
*	o grafo permanece conexo
**************************************************************************/
TpGrafo* removeTarefa(TpGrafo* , int );

/***************************************************************************
*Função: 
*	salvarTarefa
*
*Descrição
*	Função para auxiliar a gravaçao dos dados em arquivo
*	Grava conforme o padrao os dados de uma tarefa no arquivo passado
*
*Parâmetros
*	FILE* = arquivo no qual vao ser escritas as tarefas
*	TpTarefa* = tarefa a ser escrita no arquivo
*	
*Valor retornado
*	void
*
*Assertiva de entrada
*	TpTarefa* != NULL
*	FILE* != NULL
*
*Assertiva de saída
*	o ponteiro no arquivo estara apontando para o inicio de uma nova linha no final do arquivo
**************************************************************************/
void salvaTarefa(FILE* , TpTarefa* );


/***************************************************************************
*Função: 
*	salvaremArquivo
*
*Descrição
*	Função para gravar as mudanças de um grafo em arquivo
*	Grava conforme o padrao do trabalho
*
*Parâmetros
*	FILE* = arquivo no qual vao ser escritas as tarefas
*	TpGrafo* = grafo do qual se vai obter todas as tarefas a serem salvas
*	
*Valor retornado
*	void
*
*Assertiva de entrada
*	TpGrafo* != NULL
*	FILE* != NULL
*
*Assertiva de saída
*	o ponteiro no arquivo estara apontando para o inicio de uma nova linha no final do arquivo
*	os dados no arquivo serão os mesmos do grafo no fim da execução
**************************************************************************/
void salvarEmArquivo(TpGrafo* );

TpGrafo* editaTarefa(TpGrafo* , int);
TpGrafo* adicionaTarefa(TpGrafo* );
