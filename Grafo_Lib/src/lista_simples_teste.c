#include <lista_simples.h>
#include <gtest/gtest.h>

TEST (CriaLista, Testa_Lista_Simples) {
	TpListaSimples l;
	
	ASSERT_EQ(EXIT_SUCCESS, cria_LS(&l));
	ASSERT_EQ(l.ini, l.fim);
	ASSERT_EQ(0, l.tam);
}

TEST (DestroiLista, Testa_Lista_Simples) {
	TpListaSimples l;
	cria_LS(&l);
	TpVertex vertex1 = {0, 0, "NOME", 0};
	TpVertex vertex2 = {0, 0, "NOME2", 1};

	insere_inicio_LS(&l, vertex1);
	insere_inicio_LS(&l, vertex2);

	ASSERT_EQ(EXIT_SUCCESS, destroi_LS(&l));
}

TEST (Insere_Elemento_Inicio, Testa_Lista_Simples) {
	TpListaSimples l;
	TpVertex vertex = {0, 0, "NOME", 0};

	cria_LS(&l);

	ASSERT_EQ(EXIT_SUCCESS, insere_inicio_LS(&l, vertex));
	ASSERT_NE(l.ini, l.fim);
}

TEST (Insere_Elemento_Fim, Testa_Lista_Simples) {
	TpListaSimples l;
	TpVertex vertex = {0, 0, "NOME", 0};

	cria_LS(&l);

	ASSERT_EQ(EXIT_SUCCESS, insere_fim_LS(&l, vertex));
	ASSERT_NE(l.ini, l.fim);
}

TEST (ChecaVazia, Testa_Lista_Simples) {
	TpListaSimples l;
	cria_LS(&l);

	ASSERT_EQ(l.ini == l.fim, checa_vazia_LS(&l));
}

TEST (ProcuraId, Testa_Lista_Simples) {
	TpListaSimples l;
	cria_LS(&l);
	char string[] = "Olha la";

	ASSERT_EQ(ERRO, procura_id_LS(&l, string));

	TpVertex vertex1 = {0, 0, "NOME", 0};
	TpVertex vertex2 = {0, 0, "NOME2", 1};

	insere_inicio_LS(&l, vertex1);
	insere_inicio_LS(&l, vertex2);
	
	ASSERT_EQ(ERRO, procura_id_LS(&l, string));
	ASSERT_EQ(0, procura_id_LS(&l, vertex1.nome));
	ASSERT_EQ(1, procura_id_LS(&l, vertex2.nome));
}

TEST (RetornaIndex, Testa_Lista_Simples) {
	TpListaSimples l;
	cria_LS(&l);
	char string[] = "Olha la";

	ASSERT_EQ(ERRO, retorna_index_LS(&l, string));

	TpVertex vertex1 = {0, 0, "NOME", 0};
	TpVertex vertex2 = {0, 0, "NOME2", 1};

	insere_inicio_LS(&l, vertex1);
	insere_inicio_LS(&l, vertex2);

	ASSERT_EQ(ERRO, retorna_index_LS(&l, string));
	ASSERT_EQ(1, retorna_index_LS(&l, vertex1.nome));
	ASSERT_EQ(0, retorna_index_LS(&l, vertex2.nome));
}

TEST (RemoveElemento, Testa_Lista_Simples) {
	TpListaSimples l;
	char nome[TAM_MAX];
	TpVertex vertex;
	cria_LS(&l);
	
	ASSERT_EQ(EXIT_FAILURE, remove_elemento_LS(&l, nome, &vertex));

	TpVertex vertex1 = {0, 0, "NOME", 0};
	TpVertex vertex2 = {1.0, 0, "NOME2", 1};
	TpVertex vertex3 = {2.0, 0, "NOME3", 2};
	TpVertex vertex4 = {3.0, 0, "NOME4", 3};

	insere_inicio_LS(&l, vertex1);
	insere_inicio_LS(&l, vertex2);
	insere_inicio_LS(&l, vertex3);
	insere_inicio_LS(&l, vertex4);

	strcpy(nome, "NAO_TEM");

	EXPECT_EQ(EXIT_FAILURE, remove_elemento_LS(&l, nome, &vertex));


	EXPECT_EQ(EXIT_SUCCESS, remove_elemento_LS(&l, vertex1.nome, &vertex));
	EXPECT_EQ(0, strcmp(vertex1.nome, vertex.nome));

	insere_inicio_LS(&l, vertex1);
	EXPECT_EQ(EXIT_SUCCESS, remove_elemento_LS(&l, vertex3.nome, &vertex));
	EXPECT_EQ(0, strcmp(vertex3.nome, vertex.nome));

	insere_inicio_LS(&l, vertex3);
	EXPECT_EQ(EXIT_SUCCESS, remove_elemento_LS(&l, vertex3.nome, &vertex));
	EXPECT_EQ(0, strcmp(vertex3.nome, vertex.nome));

	insere_inicio_LS(&l, vertex3);
	EXPECT_EQ(EXIT_SUCCESS, remove_min_LS(&l, &vertex));
	EXPECT_FLOAT_EQ(0.0, vertex.distancia);

}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS(); 	
}
