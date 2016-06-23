#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operaGrafo.h"
#include "gtest/gtest.h"


char* file = const_cast<char*>("arquivoTeste");

/*
  Testa função de inicialização 
  
  Verifica se os ponteiros foram atualizados
  Verifica se a quantidade de elementos foi definida como 0
*/
TEST(TpGrafo, testaInicializa){

  TpGrafo* grafo = inicializa();

  ASSERT_EQ(grafo->vertices == NULL, 1);
  EXPECT_EQ(grafo->numero_vertices, 0);
}

/*
  Testa função de adicionaVertice
  
  cria duas tarefa, adiciona elas ao grafo.
  verifica se a inserçao em um grafo vazio foi feito corretamente
  verifica se a inserçao em um grafo nao vazio foi feito corretamente
  verifica se a estrutura nao foi corrompida

*/
TEST(TpGrafo, testaAdicionaVertice){

  TpGrafo* grafo = inicializa();
  TpTarefa* tarefa1 = (TpTarefa*)malloc(sizeof(TpTarefa));

  tarefa1->id_tarefa = 100;
  strcpy(tarefa1->nome_tarefa, "primeira tarefa");
  tarefa1->tarefa_executada = 0;
  tarefa1->duracao_tarefa = 3;
  tarefa1->inicio_min_tarefa = 0;
  tarefa1->pre_requisitos_tarefa = 0;

  TpTarefa* tarefa2 = (TpTarefa*)malloc(sizeof(TpTarefa));

  tarefa2->id_tarefa = 102;
  strcpy(tarefa2->nome_tarefa, "segunda tarefa");
  tarefa2->tarefa_executada = 1;
  tarefa2->duracao_tarefa = 2;
  tarefa2->inicio_min_tarefa = 3;
  tarefa2->pre_requisitos_tarefa = 1;
  tarefa2->requisitos = (int*)malloc(2*sizeof(int));
  tarefa2->requisitos[0] = 100;

  grafo = adicionaVertice(grafo, tarefa1);
  grafo = adicionaVertice(grafo, tarefa2);

  EXPECT_EQ(grafo->vertices->tarefa->id_tarefa, 100);
  EXPECT_STREQ(grafo->vertices->tarefa->nome_tarefa, "primeira tarefa");  
  EXPECT_EQ(grafo->vertices->tarefa->tarefa_executada, 0);
  EXPECT_EQ(grafo->vertices->tarefa->duracao_tarefa, 3);
  EXPECT_EQ(grafo->vertices->tarefa->inicio_min_tarefa, 0);
  EXPECT_EQ(grafo->vertices->tarefa->pre_requisitos_tarefa, 0);


  EXPECT_EQ(grafo->vertices->prox->tarefa->id_tarefa, 102);
  EXPECT_STREQ(grafo->vertices->prox->tarefa->nome_tarefa, "segunda tarefa");  
  EXPECT_EQ(grafo->vertices->prox->tarefa->tarefa_executada, 1);
  EXPECT_EQ(grafo->vertices->prox->tarefa->duracao_tarefa, 2);
  EXPECT_EQ(grafo->vertices->prox->tarefa->inicio_min_tarefa, 3);
  EXPECT_EQ(grafo->vertices->prox->tarefa->pre_requisitos_tarefa, 1);
  EXPECT_EQ(grafo->vertices->prox->tarefa->requisitos[0], 10);

  EXPECT_EQ(grafo->vertices->prox->prox == NULL, 1);
}


/*
  Testa função de leitor
  
  Le o grafo de um arquivo de teste, compara os valores salvos com os valores reais
  verifica se a estrutura nao foi corrompida

*/
TEST(TpGrafo, testaLeitor){

  TpGrafo* grafo = inicializa();
  grafo = leitor(grafo, file);

  EXPECT_EQ(grafo->vertices->tarefa->id_tarefa, 100);
  EXPECT_STREQ(grafo->vertices->tarefa->nome_tarefa, "primeira tarefa");  
  EXPECT_EQ(grafo->vertices->tarefa->tarefa_executada, 0);
  EXPECT_EQ(grafo->vertices->tarefa->duracao_tarefa, 3);
  EXPECT_EQ(grafo->vertices->tarefa->inicio_min_tarefa, 0);
  EXPECT_EQ(grafo->vertices->tarefa->pre_requisitos_tarefa, 0);


  EXPECT_EQ(grafo->vertices->prox->tarefa->id_tarefa, 102);
  EXPECT_STREQ(grafo->vertices->prox->tarefa->nome_tarefa, "segunda tarefa");  
  EXPECT_EQ(grafo->vertices->prox->tarefa->tarefa_executada, 0);
  EXPECT_EQ(grafo->vertices->prox->tarefa->duracao_tarefa, 2);
  EXPECT_EQ(grafo->vertices->prox->tarefa->inicio_min_tarefa, 3);
  EXPECT_EQ(grafo->vertices->prox->tarefa->pre_requisitos_tarefa, 2);
  EXPECT_EQ(grafo->vertices->prox->tarefa->requisitos[0], 100);
  EXPECT_EQ(grafo->vertices->prox->tarefa->requisitos[1], 101);

  EXPECT_EQ(grafo->vertices->prox->prox == NULL, 1);
}


int main(int argc, char* *argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}