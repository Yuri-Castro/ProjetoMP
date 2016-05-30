#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <grafo.h>
#include <gtest/gtest.h>

TEST (LeGrafo, TestaGrafo) {
	TpGrafo grafo;

	TpVertex vertex1, vertex2;
	
	vertex1.id = 0;
	strcpy(vertex1.nome, "A");

	vertex2.id = 2;
	strcpy(vertex2.nome, "B");

	FILE *input = NULL;

	ASSERT_EQ(EXIT_FAILURE, le_grafo(input, &grafo));

	input = fopen("TestFile.txt", "r");

	ASSERT_EQ(EXIT_SUCCESS, le_grafo(input, &grafo));
	
	EXPECT_EQ(0, strcmp(vertex1.nome, grafo.vertices.ini->prox->vertice.nome));
	EXPECT_EQ(vertex1.id, grafo.vertices.ini->prox->vertice.id);

	EXPECT_EQ(0, strcmp(vertex1.nome, grafo.vertices_origem.ini->prox->vertice.nome));
	EXPECT_EQ(vertex1.id, grafo.vertices_origem.ini->prox->vertice.id);

	EXPECT_EQ(0, strcmp(vertex1.nome, grafo.adjacencia[0].fim->key.origem.nome));
	EXPECT_EQ(vertex1.id, grafo.adjacencia[0].fim->key.origem.id);
	EXPECT_EQ(0, strcmp(vertex2.nome, grafo.adjacencia[0].fim->key.destino.nome));
	EXPECT_EQ(vertex2.id, grafo.adjacencia[0].fim->key.destino.id);
	EXPECT_EQ(4.0, grafo.adjacencia[0].fim->key.peso);
}

TEST (EscreveGrafo, TestaGrafo) {
	TpGrafo grafo;

	FILE *input = NULL, *output = NULL;

	ASSERT_EQ(EXIT_FAILURE, escreve_grafo(output, &grafo));

	input = fopen("TestFile.txt", "r");
	output = fopen("Output.txt", "w");

	le_grafo(input, &grafo);

	ASSERT_EQ(EXIT_SUCCESS, escreve_grafo(output, &grafo));
	
	/* Ao comparar os arquivos gerados é possível perceber a corretude da função; */
}

TEST (InsereVertex, TestaGrafo) {
	TpGrafo grafo;

	TpVertex vertex1;
	
	FILE *input = NULL;

	input = fopen("TestFile.txt", "r");

	le_grafo(input, &grafo);
	
	strcpy(vertex1.nome, "ABCD");
	vertex1.id = (grafo.vertices.tam) - 1;

	ASSERT_EQ(EXIT_FAILURE, insere_vertex(&grafo, vertex1, ORIGEM));
	
	strcpy(vertex1.nome, "MEU_NOME");
	
	ASSERT_EQ(EXIT_SUCCESS, insere_vertex(&grafo, vertex1, ORIGEM));
	ASSERT_EQ(vertex1.id, grafo.vertices.fim->vertice.id);
	ASSERT_EQ(vertex1.id, grafo.vertices_origem.fim->vertice.id);
}

TEST (RemoveVertex, TestaGrafo) {
	TpGrafo grafo;
	TpVertex vertex1;
	char nome[TAM_MAX];

	FILE *input = NULL;

	input = fopen("TestFile.txt", "r");

	strcpy(nome, "MEU_NOME");

	le_grafo(input, &grafo);

	ASSERT_EQ(EXIT_FAILURE, remove_vertex(&grafo, &vertex1, nome));

	strcpy(nome, "ABCD");

	ASSERT_EQ(EXIT_SUCCESS, remove_vertex(&grafo, &vertex1, nome));
	ASSERT_EQ(0, strcmp(vertex1.nome, nome));

	ASSERT_EQ( ((grafo.adjacencia[3].inicio) == (grafo.adjacencia[3].fim)), checa_vazia_LD(&(grafo.adjacencia[3])));
	

}

TEST (InsereAresta, TestaGrafo) {
	TpGrafo grafo;
	char origem[TAM_MAX], destino[TAM_MAX];
	float peso;

	strcpy(origem, "MP");
	strcpy(destino, "MP");
	FILE *input;

	peso = 5.0;

	input = fopen("TestFile.txt", "r");
	
	le_grafo(input, &grafo);

	ASSERT_EQ(EXIT_FAILURE, insere_aresta(&grafo, origem, destino, peso));

	strcpy(origem, "A");

	EXPECT_EQ(EXIT_FAILURE, insere_aresta(&grafo, origem, destino, peso));
	EXPECT_EQ(EXIT_FAILURE, insere_aresta(&grafo, destino, origem, peso));

	strcpy(destino, "ABC");

	EXPECT_EQ(EXIT_SUCCESS, insere_aresta(&grafo, origem, destino, peso));
	EXPECT_EQ(peso, grafo.adjacencia[0].inicio->proxima->key.peso);

	strcpy(origem, "B");
	strcpy(destino, "ABCD");

	EXPECT_EQ(EXIT_SUCCESS, insere_aresta(&grafo, origem, destino, peso));
	EXPECT_FLOAT_EQ(5.0, grafo.adjacencia[1].inicio->proxima->key.peso);
}

TEST (RemoveAresta, TestaGrafo) {
	TpGrafo grafo;
	char origem[TAM_MAX], destino[TAM_MAX];

	FILE *input;

	input = fopen("TestFile.txt", "r");

	le_grafo(input, &grafo);

	strcpy(origem, "MP");
	strcpy(destino, "MP");

	ASSERT_EQ(EXIT_FAILURE, remove_aresta(&grafo, origem, destino));

	strcpy(origem, "B");
	
	ASSERT_EQ(EXIT_FAILURE, remove_aresta(&grafo, origem, destino));

	strcpy(origem, "A");
	strcpy(destino, "ABC");

	EXPECT_EQ(EXIT_FAILURE, remove_aresta(&grafo, origem, destino));

	strcpy(destino, "B");

	EXPECT_EQ(EXIT_SUCCESS, remove_aresta(&grafo, origem, destino));
	EXPECT_EQ(1.0, grafo.adjacencia[0].fim->key.peso);

}

TEST (CalculaDistancia, TestaGrafo) {
	TpGrafo grafo;

	FILE *input = NULL;

	input = fopen("TestFile.txt", "r");

	le_grafo(input, &grafo);

	char strA[TAM_MAX], strB[TAM_MAX], strABC[TAM_MAX];

	strcpy(strA, "A");
	strcpy(strB, "B");
	strcpy(strABC, "ABC");

	ASSERT_FLOAT_EQ(ERRO_F, calculaDistancia(&grafo, strB, strABC));
	EXPECT_FLOAT_EQ(3.0, calculaDistancia(&grafo, strA, strABC));
	EXPECT_FLOAT_EQ(4.0, calculaDistancia(&grafo, strA, strB));
}

TEST (GrafoConsistente, TestaGrafo) {
	TpGrafo grafo;
	TpInfo info;

	FILE *input = NULL;

	input = fopen("TestFile.txt", "r");

	le_grafo(input, &grafo);

	strcpy(info.origem.nome, "A");
	strcpy(info.destino.nome, "MP");
	info.origem.id = 0;
	info.origem.id = 5;
	info.peso = 5.0;

	ASSERT_EQ(EXIT_SUCCESS, grafoConsistente(&grafo));

	insere_LD(&(grafo.adjacencia[0]), info);

	ASSERT_EQ(EXIT_FAILURE, grafoConsistente(&grafo));

}

TEST (GrafoConexo, TestaGrafo) {
	TpGrafo grafo;
	TpVertex vertex;

	FILE *input = NULL;

	input  = fopen("TestFile.txt", "r");

	le_grafo(input, &grafo);

	ASSERT_EQ(EXIT_SUCCESS, grafoConexo(&grafo));

	strcpy(vertex.nome, "MP");
	vertex.id = 500;

	insere_vertex(&grafo, vertex, NAO_ORIGEM);

	ASSERT_EQ(EXIT_FAILURE, grafoConexo(&grafo));
}

TEST (DestroiGrafo, TestaGrafo) {
	TpGrafo grafo;

	TpVertex vertex1, vertex2;
	
	vertex1.id = 0;
	strcpy(vertex1.nome, "A");

	vertex2.id = 2;
	strcpy(vertex2.nome, "B");

	FILE *input = NULL;

	input = fopen("TestFile.txt", "r");


	/* Como as funções para destruir listas já foram testadas, sabe-se que elas estão corretas. Por isso, não é necessário realizar muitos testes; */
	le_grafo(input, &grafo);
	ASSERT_EQ(EXIT_SUCCESS, destroi_grafo(&grafo));
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
