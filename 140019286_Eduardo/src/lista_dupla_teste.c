#include <lista_dupla.h>
#include <gtest/gtest.h>

TEST (CriaLista, Teste_Lista_Dupla) {
	TpListaDupla lista;
	
	ASSERT_EQ(EXIT_SUCCESS, cria_LD(&lista));
	ASSERT_EQ(lista.fim, lista.inicio);
	ASSERT_EQ(lista.fim->proxima, lista.inicio->proxima);
	ASSERT_EQ(lista.fim->anterior, lista.inicio->anterior);
};

TEST (ChecaVazia, Teste_Lista_Dupla) {
	TpListaDupla lista;
	cria_LD(&lista);

	ASSERT_EQ((lista.inicio == lista.fim), checa_vazia_LD(&lista));
}

TEST (InsereElemento, Teste_Lista_Dupla) {
	TpListaDupla lista;
	TpVertex vertex1 = {0, 0, "NOME", 0};
	TpVertex vertex2 = {0, 0, "NOME2", 1};
	TpInfo key;
	key.origem = vertex1;
	key.destino = vertex2;
	key.peso = 4.0;

	cria_LD(&lista);
	ASSERT_EQ(EXIT_SUCCESS, insere_LD(&lista, key));
	ASSERT_EQ(lista.inicio->proxima->key.peso, key.peso);
	ASSERT_EQ(lista.inicio->proxima->key.peso, lista.fim->key.peso);
	
	ASSERT_EQ(EXIT_SUCCESS, insere_LD(&lista, key));
	ASSERT_EQ(lista.inicio->proxima->proxima->key.peso, key.peso);
	ASSERT_EQ(lista.inicio->proxima->proxima->key.peso, lista.fim->key.peso);
}

TEST (ProcuraChave, Teste_Lista_Dupla) {
	TpListaDupla lista;
	TpVertex vertex1 = {0, 0, "NOME", 0};
	TpVertex vertex2 = {0, 0, "NOME2", 1};
	TpInfo key, key2;
	key.origem = vertex1;
	key.destino = vertex2;
	key.peso = 4.0;
	key2.origem = vertex2;
	key2.destino = vertex1;
	key2.peso = 2.0;

	cria_LD(&lista);
	
	ASSERT_EQ(ERRO, procura_chave_LD(&lista, 5));
	
	insere_LD(&lista, key);
	insere_LD(&lista, key2);

	ASSERT_EQ(ERRO, procura_chave_LD(&lista, 4));
	ASSERT_EQ(0, procura_chave_LD(&lista, 0));
	ASSERT_EQ(1, procura_chave_LD(&lista, 1));
}

TEST (RemoveElemento, Teste_Lista_Dupla) {
	TpListaDupla lista;

	TpVertex vertex1 = {0, 0, "NOME", 0};
	TpVertex vertex2 = {0, 0, "NOME2", 1};
	TpInfo key, aux;
	key.origem = vertex1;
	key.destino = vertex2;
	key.peso = 4.0;

	cria_LD(&lista);
	insere_LD(&lista, key);
	insere_LD(&lista, key);

	ASSERT_EQ(EXIT_SUCCESS, remove_elemento_LD(&lista, &aux, 0));
	remove_elemento_LD(&lista, &aux, 0);
	ASSERT_EQ(key.peso, aux.peso);	
}

TEST (DestroiLista, Teste_Lista_Dupla) {
	TpListaDupla lista;
	TpVertex vertex1 = {0, 0, "NOME", 0};
	TpVertex vertex2 = {0, 0, "NOME2", 1};
	TpInfo key, key2;
	key.origem = vertex1;
	key.destino = vertex2;
	key.peso = 4.0;
	key2.origem = vertex2;
	key2.destino = vertex1;
	key2.peso = 2.0;

	cria_LD(&lista);
	ASSERT_EQ(EXIT_SUCCESS, destroi_LD(&lista));

	cria_LD(&lista);
	insere_LD(&lista, key);
	insere_LD(&lista, key2);
	ASSERT_EQ(EXIT_SUCCESS, destroi_LD(&lista));
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
