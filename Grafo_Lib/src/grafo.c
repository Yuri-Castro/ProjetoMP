#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <grafo.h>

/*
 * Função 'le_grafo': Lê as informações presentes
 * em um arquivo de 'input' para o grafo. A leitura
 * é feita seguindo uma formatação específica de arquivo:
 * 
 * LINHA 1: <VÉRTICE 1>, <VÉRTICE 2>, ..., <VÉRTICE n>
 * LINHA 2: <ORIGEM 1>, <ORIGEM 2>, ..., <ORIGEM n>
 * LINHAS RESTANTES: <ORIGEM>, <DESTINO>, <PESO>
 *					 <ORIGEM>, <DESTINO>, <PESO>
 *					               .
 *					               .
 *					               .
 *					 <ORIGEM>, <DESTINO>, <PESO>
 */

int le_grafo(FILE *input, TpGrafo *grafo) {
	char nome[TAM_MAX]; /* O nome tem o tamanho máximo de 100 caracteres; */
	char aux;
	float peso;
	int i, id;
	celula *cell;
	TpVertex tmp, tmp2;
	TpInfo info;
	memset(nome, '\0', TAM_MAX);

	if(input == NULL) {
		return (EXIT_FAILURE);
	}

	/* Cria as listas necessárias para operar o grafo; */
	cria_LS(&(grafo->vertices));
	cria_LS(&(grafo->vertices_origem));
	i = 0;	
	id = 0;
	grafo->numero_vertices = 0;

	/* Loop que adiciona os vértices do grafo (linha 1); */
	while(i >= 0) {
		aux = fgetc(input);
		switch (aux) {
			case ',':
				strcpy(tmp.nome, nome);
				tmp.id = id;
				id++;
				insere_fim_LS(&(grafo->vertices), tmp);
				grafo->numero_vertices++;
				memset(nome, '\0', 100);
				i = 0;
				break;
			case ' ':
				break;
			case '\n': /* Encontra o final da linha e sai do loop; */
				strcpy(tmp.nome, nome);
				tmp.id = id;
				id++;
				insere_fim_LS(&(grafo->vertices), tmp);
				grafo->numero_vertices++;
				memset(nome, '\0', 100);
				i = -1;
				break;
			default:
				nome[i] = aux;
				i++;
		}
	}

	/* TODO: mudei de número de origens para número de vértices; */
	grafo->adjacencia = (TpListaDupla *)malloc(grafo->numero_vertices * sizeof(TpListaDupla));
	if(grafo->adjacencia == NULL) {
		return (EXIT_FAILURE);
	}

	for(i = 0, cell = grafo->vertices.ini->prox; i < grafo->numero_vertices; i++, cell = cell->prox) {
		cria_LD(&(grafo->adjacencia[i]));
		strcpy(grafo->adjacencia[i].inicio->key.origem.nome, cell->vertice.nome);
	}

	grafo->tam_vetor_lista = grafo->numero_vertices;


	i = 0;
	grafo->numero_origens = 0;	
	/* Loop que adiciona os vértices origem do grafo (linha 2); */
	while(i >= 0) {
		aux = fgetc(input);
		switch (aux) {
			case ',':
				strcpy(tmp.nome, nome);
				tmp.id = procura_id_LS(&(grafo->vertices), nome);
				insere_fim_LS(&(grafo->vertices_origem), tmp);
				grafo->numero_origens++;
				memset(nome, '\0', 100);
		    	i = 0;
			break;
			case ' ':
				break;
			case '\n': /* Encontra o final da linha e sai do loop; */
				strcpy(tmp.nome, nome);
				tmp.id = procura_id_LS(&(grafo->vertices), nome);
				insere_fim_LS(&(grafo->vertices_origem), tmp);
				grafo->numero_origens++;
				memset(nome, '\0', 100);	
				i = -1;
				break;
			default:
				nome[i] = aux;
				i++;
		}
	}
	
	/* Loop para ler as arestas (restante das linhas); */
	while(!feof(input) && !ferror(input)) {
		i = 0;
		
		while(i >= 0) {
			aux = fgetc(input);
			if(feof(input)) {
				break;		
			}
			switch(aux) {
				case ',':
					strcpy(tmp.nome, nome);
					tmp.id = procura_id_LS(&(grafo->vertices), nome);
					memset(nome, '\0', 100);
					i = -1;	
					break;
				case ' ':
					break;
				default:
					nome[i] = aux;
					i++;
			}	
		}

		if(feof(input)) {
			break;
		}
		aux = fgetc(input); /* Captura o 'space'; */
		i = 0;

		while(i >= 0) {
			aux = fgetc(input);
			switch(aux) {
				case ',':
					strcpy(tmp2.nome, nome);
					tmp2.id = procura_id_LS(&(grafo->vertices), nome);
					memset(nome, '\0', 100);
					i = -1;	
					break;
				case ' ':
					break;
				default:
					nome[i] = aux;
					i++;
			}	
		}

		aux = fgetc(input); /* Captura o 'space'; */
		fscanf(input,"%f",&peso);
		if(peso <= 0) { /* O peso deve ser maior do que zero; */
			return (EXIT_FAILURE);
		}
		info.peso = peso;
		info.origem = tmp;
		info.destino = tmp2;
		id = retorna_index_LS(&(grafo->vertices), tmp.nome);
		insere_LD(&(grafo->adjacencia[id]), info);
		aux = fgetc(input); /* Captura o '\n'; */
	}

	fclose(input); /* O arquivo não será mais usado, portanto ele é fechado; */	
	return EXIT_SUCCESS;
}

int escreve_grafo(FILE *output, TpGrafo *grafo) {

	if(output == NULL) {
		return (EXIT_FAILURE);
	}
	
	if(checa_vazia_LS(&(grafo->vertices))) {
		return (EXIT_FAILURE);
	}
	/*					VÁRIAVEIS;				 */
	celula *aux; /* Iterator para a lista duplamente encadeada; */
	TpCelula *aux2; /* Iterator para a lista simplesmente encadeada; */
	TpInfo info;
	char token1[] = ", ";
	char token2 = '\n';
	int i;
	
	/*					ALGORITMO;				 */
	for(aux = grafo->vertices.ini->prox; aux != grafo->vertices.fim; aux = aux->prox) {
		fprintf(output, "%s", aux->vertice.nome);
		fprintf(output, "%s", token1);
	}
	fprintf(output, "%s", aux->vertice.nome);
	fprintf(output, "%c", token2);

	for(aux = grafo->vertices_origem.ini->prox; aux != grafo->vertices_origem.fim; aux = aux->prox) {
		fprintf(output, "%s", aux->vertice.nome);
		fprintf(output, "%s", token1);
	}
	fprintf(output, "%s", aux->vertice.nome);
	fprintf(output, "%c", token2);

	for(i = 0; i < grafo->tam_vetor_lista; i++) {
		for(aux2 = grafo->adjacencia[i].inicio->proxima; aux2 != NULL; aux2 = aux2->proxima) {
			info = aux2->key;
			fprintf(output, "%s", info.origem.nome);
			fprintf(output, "%s", token1);
			fprintf(output, "%s", info.destino.nome);
			fprintf(output, "%s", token1);
			fprintf(output, "%.1f", info.peso);
			fprintf(output, "%c", token2);
		}
	}

	fclose(output);
	return (EXIT_SUCCESS);
}

int insere_vertex(TpGrafo *grafo ,TpVertex vertice, int type) {

	/* Nesse caso o vértice já existe no grafo; */
	if(procura_id_LS(&(grafo->vertices), vertice.nome) != ERRO) {
		return (EXIT_FAILURE);	
	}

	insere_fim_LS(&(grafo->vertices), vertice);
	grafo->numero_vertices++;

	if(type == ORIGEM) {
		insere_fim_LS(&(grafo->vertices_origem), vertice);
		grafo->numero_origens++;
	}

	return (EXIT_SUCCESS);
}

int remove_vertex(TpGrafo *grafo, TpVertex *vertice, char *nome) {
	int i, j;
	TpCelula *aux;	
	TpInfo info;

	/* Nesse caso o vértice não existe no grafo; */
	if(procura_id_LS(&(grafo->vertices), nome) == ERRO) {
		return (EXIT_FAILURE);	
	}

	/* Retira a aresta que possuí esse vértice; */
	for(i = 0; i < grafo->tam_vetor_lista; i++) {
		for(j = 0, aux = grafo->adjacencia[i].inicio->proxima; aux != NULL; j++, aux = aux->proxima) {
			/* Nesse caso pode-se liberar a lista; */
			if(aux == grafo->adjacencia[i].inicio->proxima) {
				destroi_LD(&(grafo->adjacencia[i]));
				cria_LD(&(grafo->adjacencia[i])); /* Cria uma lista vazia no lugar para ser reusada; */
				break;
			}

			if(strcmp(aux->key.origem.nome, nome) == 0) {
				remove_elemento_LD(&(grafo->adjacencia[i]), &info, j);	
			}
			else if(strcmp(aux->key.destino.nome, nome) == 0) {
				remove_elemento_LD(&(grafo->adjacencia[i]), &info, j);
			}
		}
	}

	remove_elemento_LS(&(grafo->vertices), nome, vertice);
	grafo->numero_vertices--;

	if(procura_id_LS(&(grafo->vertices_origem), nome) != ERRO) {
		remove_elemento_LS(&(grafo->vertices_origem), nome, vertice);
		grafo->numero_origens--;
	}
//	destroi_LD(&(grafo->adjacencia[i]));

	return (EXIT_SUCCESS);
}

int insere_aresta(TpGrafo *grafo, char *origem, char *destino, float peso) {
	TpVertex vertex_origem, vertex_destino;
	TpInfo info;
	int i;
	
	vertex_origem.id = procura_id_LS(&(grafo->vertices), origem);
	vertex_destino.id = procura_id_LS(&(grafo->vertices), destino);

	/* Algum dos vértices não existe; */
	if(vertex_origem.id == ERRO || vertex_destino.id == ERRO) {
		return (EXIT_FAILURE);
	}

	if(peso <= 0) {
		return (EXIT_FAILURE);
	}

	strcpy(vertex_origem.nome, origem);
	strcpy(vertex_destino.nome, destino);

	for(i = 0; i < grafo->tam_vetor_lista; i++) {
		if(!checa_vazia_LD(&(grafo->adjacencia[i]))) {	
			if(strcmp(grafo->adjacencia[i].inicio->proxima->key.origem.nome, origem) == 0) {
				break;
			}
		}
		else {
			break;
		}
	}

	info.origem = vertex_origem;
	info.destino = vertex_destino;
	info.peso = peso;

	/* Insere em uma lista vazia ou em uma lista que tenha o vértice origem da aresta; */
	if(i < grafo->tam_vetor_lista) {
		insere_LD(&(grafo->adjacencia[i]), info);
		strcpy(grafo->adjacencia[i].inicio->key.origem.nome, info.origem.nome);
	}

	/* Tem que criar uma lista; */
	else {
		grafo->tam_vetor_lista++;
		grafo->adjacencia = (TpListaDupla *)realloc(grafo->adjacencia, grafo->tam_vetor_lista * sizeof(TpListaDupla));
		assert(grafo->adjacencia != NULL);
		cria_LD(&(grafo->adjacencia[i]));
		insere_LD(&(grafo->adjacencia[i]), info);
		strcpy(grafo->adjacencia[i].inicio->key.origem.nome, info.origem.nome);
	}

	return EXIT_SUCCESS;
}

int remove_aresta(TpGrafo *grafo, char *origem, char *destino) {
	TpInfo info;
	int id1, id2;
	int index, local;

	/* Se algum dos vértices não existe, não existe aresta; */
	id1 = procura_id_LS(&(grafo->vertices), origem);
	id2 = procura_id_LS(&(grafo->vertices), destino);
	
	if( (id1 == ERRO) || (id2 == ERRO) ) {
		return (EXIT_FAILURE);
	}

	/* Verifica se a origem é realmente uma aresta origem; */	
	for(index = 0; index < grafo->tam_vetor_lista; index++) {
		if(id1 == grafo->adjacencia[index].inicio->proxima->key.origem.id) {
			break;
		}
	}

	/* A aresta não existe; */
	if(index >= grafo->tam_vetor_lista) {
		return (EXIT_FAILURE);
	}

	/* Verifica se o destino está ligado à origem; */
	local = procura_chave_LD(&(grafo->adjacencia[index]), id2);
	
	/* Os vértices não possuem uma aresta ligando eles; */
	if(local == ERRO) {
		return (EXIT_FAILURE);
	}
	
	remove_elemento_LD(&(grafo->adjacencia[index]), &info, local);

	return (EXIT_SUCCESS);
}

/* Utiliza-se o algoritmo de Dijkstra com algumas modificações para que se calcule a distância entre uma origem e um destino; */
float calculaDistancia(TpGrafo *grafo, char *origem, char *destino) {
	TpListaDupla lista;
	TpListaSimples auxiliar;
	TpCelula *aux;
	TpVertex remove;
	celula *cell;
	int i, index, found;
	float distancia, tmp, peso_origem, peso_destino;

	index = -1;
	/* Utiliza-se a busca em profundidade para verificar se exite um caminho entre os vértices; */	
	distancia = 0.0; 
	if(checa_vazia_LS(&(grafo->vertices))) {
		return ERRO_F;
	}

	if(checa_vazia_LS(&(grafo->vertices_origem))) {
		return ERRO_F;
	}

	/* Inicializa os vértices como não visitados; */
	for(cell = grafo->vertices.ini->prox; cell != NULL; cell = cell->prox) {
		cell->vertice.distancia = INFINITO;
		cell->vertice.visitado = NAO_VISITADO;
	}

	if( verifica_caminho(grafo, origem, destino) == ERRO ) {
		return ERRO_F;
	}

	/* Procura o vértice origem na lista de adjacência; */
	for(i = 0; i < grafo->tam_vetor_lista; i++) {
		if( !checa_vazia_LD(&(grafo->adjacencia[i])) ) {
			if( strcmp(grafo->adjacencia[i].inicio->proxima->key.origem.nome, origem) == 0 ) {
				index = i;
				break;	
			}
		}
	}

	/* Não encontrou vértice de origem; */	
	if(index < 0) {
		return (ERRO_F);
	}
	
	found = 0;
	/* Inicia o cálculo a partir do vértice de origem; */
	lista = grafo->adjacencia[index];
	/* Seta o vértice inicial com distância zero; */
	set_distancia(&(grafo->vertices), lista.inicio->proxima->key.origem.nome, MIN); 
	cria_LS(&auxiliar);


	for(cell = grafo->vertices.ini->prox; cell != NULL; cell = cell->prox) {
		if(strcmp(lista.inicio->proxima->key.origem.nome, cell->vertice.nome) != 0) { /* O vértice origem não é incluído; */
			insere_fim_LS(&auxiliar, cell->vertice);
		}
	}

	while(found != FOUND) {
		
		if(!checa_vazia_LD(&lista)) {
			for(aux = lista.inicio->proxima; aux != NULL; aux = aux->proxima) {
				peso_destino = verifica_distancia(&(grafo->vertices), aux->key.destino.nome);
				peso_origem = verifica_distancia(&(grafo->vertices), aux->key.origem.nome);
//				if( verifica_distancia(&(grafo->vertices), aux->key.destino.nome) > (aux->key.origem.distancia + aux->key.peso) ) {
				if(peso_destino > peso_origem + aux->key.peso) {
					//tmp = aux->key.origem.distancia + aux->key.peso;
					tmp = peso_origem + aux->key.peso;
					//printf("[CALCULA]: %s->%s-%f\n", aux->key.origem.nome, aux->key.destino.nome, tmp);
					set_distancia(&(grafo->vertices), aux->key.destino.nome, tmp);
					set_distancia(&auxiliar, aux->key.destino.nome, tmp);
				}		
				if( strcmp(aux->key.destino.nome, destino) == 0 ) {
					found = FOUND;
					distancia = tmp;
					break;
				}	
			}	
		}

		remove_min_LS(&auxiliar, &remove);
		for(i = 0; i < grafo->tam_vetor_lista; i++) {
			if(!checa_vazia_LD(&(grafo->adjacencia[i]))) {
				if(strcmp(grafo->adjacencia[i].inicio->proxima->key.origem.nome, remove.nome) == 0) {
					lista = grafo->adjacencia[i];
					break;
				}
			}
		}
	}

	return (distancia);
}

int verifica_caminho(TpGrafo *grafo, char *origem, char *destino) {
	int index;
	int sucesso, found = 0;

	/* Encontra a lista correta no vetor; */
	for(index = 0; index < grafo->tam_vetor_lista; index++) {
		if( !checa_vazia_LD(&(grafo->adjacencia[index])) ) {
			if( strcmp(grafo->adjacencia[index].inicio->proxima->key.origem.nome, origem) == 0 ) {
				found = FOUND;
				break;
			}
		}
	}	

	if(found == FOUND) {
		sucesso = DFS_rec_caminho(grafo, &(grafo->vertices), &(grafo->adjacencia[index]), origem, destino);
	}
	else {
		sucesso = ERRO;
	}

	return (sucesso);
}

int DFS_rec_caminho(TpGrafo *grafo, TpListaSimples *l_simples, TpListaDupla *lista, char *origem, char *destino) {
	TpCelula *aux;
	int i, sucesso = ERRO; 

	if(checa_vazia_LD(lista)) { 
		return (ERRO);
	}

	set_visitado(l_simples, lista->inicio->proxima->key.origem.nome);

	for(aux = lista->inicio->proxima; aux != NULL; aux = aux->proxima) {
		/* Foi encontrado um caminho entre a origem e o destino; */
		if( strcmp(aux->key.destino.nome, destino) == 0) {
			return (EXIT_SUCCESS);
		}

		if( verifica_visitado(l_simples, aux->key.destino.nome) == NAO_VISITADO ) {
			
			/* Manda o vértice origem correto para buscar os que são adjacentes a ele; */	
			for(i = 0; i < grafo->tam_vetor_lista; i++)	{
				if( !checa_vazia_LD(&(grafo->adjacencia[i])) ) {
					/* Só visita vértice se houver algum adjacente; */
					if( strcmp(grafo->adjacencia[i].inicio->proxima->key.origem.nome, aux->key.destino.nome) == 0) {
						sucesso = DFS_rec_caminho(grafo, l_simples, &(grafo->adjacencia[i]), origem, destino);
					}
				}
			}

		}
	}

	return (sucesso); 
}

int grafoConsistente(TpGrafo *grafo) { 
	TpCelula *aux;
	int i;

	for(i = 0; i < grafo->numero_vertices; i++) {
		for(aux = grafo->adjacencia[i].inicio->proxima; aux != NULL; aux = aux->proxima) {
			if(procura_id_LS(&(grafo->vertices), aux->key.origem.nome) == ERRO) {
				return (EXIT_FAILURE);	
			}
			else if(procura_id_LS(&(grafo->vertices), aux->key.destino.nome) == ERRO) {
				return (EXIT_FAILURE);
			}
			else if(aux->key.peso <= 0) {
				return (EXIT_FAILURE);
			}
		}
	}

	return EXIT_SUCCESS;
}


/* O algoritmo de busca em profundidade é utilizado para verificar
 * se o grafo é conexo; */

int grafoConexo(TpGrafo *grafo) {
	celula *cell;
	int count;

	count = 0;

	if(checa_vazia_LS(&(grafo->vertices))) {
		return (EXIT_FAILURE);
	}
		
	/*Inicializa os vértices de cada aresta; */	
	for(cell = grafo->vertices.ini->prox; cell != NULL; cell = cell->prox) {
		cell->vertice.visitado = NAO_VISITADO;	
	}

	DFS(grafo, &(grafo->vertices), &count);

	if(count != grafo->numero_vertices) {
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

void DFS(TpGrafo *grafo, TpListaSimples *lista, int *count) {
	int i;


	for(i = 0; i < grafo->tam_vetor_lista; i++) {

		if(!checa_vazia_LD(&(grafo->adjacencia[i]))) {
			/* Verifica se o grafo já foi visitado; */
			if(verifica_visitado(lista, grafo->adjacencia[i].inicio->proxima->key.origem.nome) == NAO_VISITADO) {
				DFS_rec(grafo, lista, &(grafo->adjacencia[i]), count);
			}
		}
	}

}

void DFS_rec(TpGrafo *grafo, TpListaSimples *l_simples, TpListaDupla *lista, int *count) {
	TpCelula *aux;
	int i;

	/* O vértice foi visitado; */	
	set_visitado(l_simples, lista->inicio->proxima->key.origem.nome);

	/* Incrementa o contador de vértices visitados; */
	(*count)++;

	for(aux = lista->inicio->proxima; aux != NULL; aux = aux->proxima) {
	
		/* Verifica se o vertice já foi visitado; */	
		if(verifica_visitado(l_simples, aux->key.destino.nome) == NAO_VISITADO) {
			/* Vai visitar o vertice; */
			for(i = 0; i < grafo->tam_vetor_lista; i++)	{
				if( !checa_vazia_LD(&(grafo->adjacencia[i])) ) {
					/* Só visita vértice se houver algum adjacente; */
					if( strcmp(grafo->adjacencia[i].inicio->proxima->key.origem.nome, aux->key.destino.nome) == 0) {
						DFS_rec(grafo, l_simples, &(grafo->adjacencia[i]), count);
						break;
					}
				}
				else if(verifica_visitado(l_simples, grafo->adjacencia[i].inicio->key.origem.nome) == NAO_VISITADO
						&& strcmp(grafo->adjacencia[i].inicio->key.origem.nome, aux->key.destino.nome) == 0) {
					(*count)++;
					break;
				}
			}
		}
	}	
}
	

int destroi_grafo(TpGrafo *grafo) {
	int i;

	destroi_LS(&(grafo->vertices));
	destroi_LS(&(grafo->vertices_origem));
	
	for(i = 0; i < grafo->numero_vertices; i++) {
		destroi_LD(&(grafo->adjacencia[i]));
	}

	free(grafo->adjacencia);

	return (EXIT_SUCCESS);
}


