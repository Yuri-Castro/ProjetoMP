#include <lista_simples.h>

/* Cria uma lista vazia; */
int cria_LS(TpListaSimples *l)
{
	l->ini = (celula *)malloc(sizeof(celula));
	if(l->ini == NULL)
	{
		printf("Erro na alocacao de memoria.\n");
		return (EXIT_FAILURE);
	}
	l->fim = l->ini;
	l->fim->prox = NULL;
	l->ini->prox = NULL;
	l->tam = 0;
	return (EXIT_SUCCESS);
}

/* Insere elemento no começo da lista; */
int insere_inicio_LS(TpListaSimples *l, TpVertex vertex)
{
	celula *c;
	c = (celula *)malloc(sizeof(celula));
	if(c == NULL)
	{
		printf("Erro na alocacao de memoria.\n");
		return (EXIT_FAILURE);
	}
	l->ini->vertice = vertex;
	c->prox = l->ini;
	l->ini = c;
	l->tam++;
	return (EXIT_SUCCESS);
}

/* Insere elemento no fim da lista; */
int insere_fim_LS(TpListaSimples *l, TpVertex vertex)
{
	l->fim->prox = (celula *)malloc(sizeof(celula));
	if(l->fim->prox == NULL)
	{
		printf("Erro na alocacao de memoria.\n");
		return (EXIT_FAILURE);
	}
	l->fim = l->fim->prox;
	l->fim->prox = NULL;
	l->fim->vertice = vertex;
	l->tam++;
	return (EXIT_SUCCESS);
}

/* Checa se a lista está vazia; */
int checa_vazia_LS(TpListaSimples *l)
{
	return (l->ini == l->fim);
}

/* Procura o identificador de um nome;*/
int procura_id_LS(TpListaSimples *l, char *nome) {
	celula *aux;
	if(checa_vazia_LS(l)) {
		return (ERRO);
	}

	aux = l->ini->prox;
	while((aux != NULL) && (strcmp(aux->vertice.nome, nome) != 0)) {
		aux = aux->prox;		
	}

	if(aux == NULL) { /* Toda a lista foi percorrida e o elemento não foi encontrado; */
		return (ERRO);
	}

	return (aux->vertice.id);
}

/* Essa função é usada para saber a localização de um 'nome' na lista de adjacência; */
int retorna_index_LS(TpListaSimples *l, char *nome) {
	celula *aux;
	int index = 0;
	if(checa_vazia_LS(l)) {
		return (ERRO);
	}

	aux = l->ini->prox;
	while((aux != NULL) && (strcmp(aux->vertice.nome, nome) != 0)) {
		aux = aux->prox;
		index++;
	}

	if(aux == NULL) {
		return (ERRO);
	}

	return index;
}

/* Verifica se o vértice foi visitado; */
int verifica_visitado(TpListaSimples *l, char *nome) {
	celula *aux;

	if(checa_vazia_LS(l)) {
		return (ERRO);
	}

	aux = l->ini->prox;
	while( (aux != NULL) && (strcmp(aux->vertice.nome, nome) != 0) ) {
		aux = aux->prox;
	}
	if(aux == NULL) {
		return (ERRO);
	}	
	else if(aux->vertice.visitado == NAO_VISITADO) {
		return (NAO_VISITADO);
	}
	else {
		return (VISITADO);
	}
}

/* Seta o vértice como visitado; */
void set_visitado(TpListaSimples *l, char *nome) {
	celula *aux;

	if(checa_vazia_LS(l)) {
		return;
	}

	aux = l->ini->prox;
	while( (aux != NULL) && (strcmp(aux->vertice.nome, nome) != 0) ) {
		aux = aux->prox;
	}
	if(aux == NULL) {
		return;
	}	
	else if(aux->vertice.visitado == NAO_VISITADO) {
		aux->vertice.visitado = VISITADO;
	}
	else {
		return;
	}
}

/* Verifica a distância do vértice a uma dado vértice; */
float verifica_distancia(TpListaSimples *l, char *nome) {
	celula *aux;

	if(checa_vazia_LS(l)) {
		return (ERRO_F);
	}

	aux = l->ini->prox;
	while( (aux != NULL) && (strcmp(aux->vertice.nome, nome) != 0) ) {
		aux = aux->prox;
	}
	if(aux == NULL) {
		return (ERRO_F);
	}	
	
	return (aux->vertice.distancia);
}

/* Seta uma nova distância para o vértice; */
void set_distancia(TpListaSimples *l, char *nome, float peso) {
	celula *aux;

	if(checa_vazia_LS(l)) {
		return;
	}
	
	if(peso <= 0) {
		return;
	}

	aux = l->ini->prox;
	while( (aux != NULL) && (strcmp(aux->vertice.nome, nome) != 0) ) {
		aux = aux->prox;
	}
	if(aux == NULL) {
		return;
	}	
	aux->vertice.distancia = peso;	
}

/* Remove um elemento da lista; */
int remove_elemento_LS(TpListaSimples *l, char *nome, TpVertex *vertice) {

	if(checa_vazia_LS(l)) {
		return (EXIT_FAILURE);
	}

	celula *aux, *ant;
	ant = l->ini;
	aux = l->ini->prox;
	while((aux != NULL) && (strcmp(aux->vertice.nome, nome) != 0)) {
		ant = aux;
		aux = aux->prox;
	}

	/* Vértice não existe na lista; */
	if(aux == NULL) {
		return (EXIT_FAILURE);
	}
	/* Primeiro elemento; */
	else if(aux == l->ini->prox) {
		l->ini->prox = aux->prox;
	}
	/* Último elemento; */
	else if(aux->prox == NULL) {
		l->fim = ant;
		ant->prox = NULL;
	}
	/* Elemento qualquer; */
	else {
		ant->prox = aux->prox;
	}

	*vertice = aux->vertice;
	free(aux);
	return (EXIT_SUCCESS);
}

/* Remove o vértice com menor ditância; */
int remove_min_LS(TpListaSimples *l, TpVertex *min) {
	/* Verifica se a lista é vazia; */
	if(checa_vazia_LS(l)) {
		return (EXIT_FAILURE);
	}

	celula *aux, *remove, *remove_ant , *ant;
	float menor = INFINITO + 1;

	remove_ant = NULL;
	remove = NULL;
	ant = l->ini;
	aux = l->ini->prox;
	while(aux != NULL) {
		if(aux->vertice.distancia < menor) {
			(*min) = aux->vertice;
			remove = aux;
			remove_ant = ant;
			menor = aux->vertice.distancia;
		}
		ant = aux;
		aux = aux->prox;
	}

	if(remove == NULL) {
		return (EXIT_FAILURE);
	}
	else if(remove == l->ini->prox) {
		l->ini->prox = remove->prox;
	}
	else if(remove->prox == NULL) {
		l->fim = remove_ant;
		remove_ant->prox = NULL;
	}
	else {
		remove_ant->prox = remove->prox;
	}

	free(remove);
	return (EXIT_SUCCESS);
}

/* Libera a memória utilizada pela lista; */
int destroi_LS(TpListaSimples *l)
{
	celula *aux, *lib;
	
	if(checa_vazia_LS(l))
	{
		printf("A lista esta vazia. Nao ha nada para mostrar.\n");
		return (EXIT_FAILURE);
	}

	for(aux = l->ini; aux != NULL;)
	{	
		lib = aux;
		aux = aux->prox;
		free(lib);
	}
	l->tam = 0;
	return (EXIT_SUCCESS);
}


