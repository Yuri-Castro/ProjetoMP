#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operaGrafo.h"
#include "gtest/gtest.h"


char* arquivoTeste = const_cast<char*>("arquivoTeste");

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
  
  Testa adicionar uma tarefa a um grafo vazio
  testa se a inserção foi feita corretamente
  testa se a estrutura de dados foi corrompida

  testa inserir uma tarefa em um grafo nao vazio
  verifica se a inserçao foi feita corretamente
  verifica se a estrutura nao foi corrompida

  testa adicionar uma tarefa com um id ja existente
  verifica a tarefa nao foi inserida
  verifica se a estrutura de dados foi corrempida

*/
TEST(TpGrafo, testaAdicionaVertice){

  TpGrafo* grafo = inicializa();

  ASSERT_EQ(grafo->vertices == NULL, 1);
  EXPECT_EQ(grafo->numero_vertices, 0);
  
  TpTarefa* tarefa1 = (TpTarefa*)malloc(sizeof(TpTarefa));

  tarefa1->id_tarefa = 100;
  strcpy(tarefa1->nome_tarefa, "primeira tarefa");
  tarefa1->tarefa_executada = 0;
  tarefa1->duracao_tarefa = 3;
  tarefa1->inicio_min_tarefa = 0;
  tarefa1->pre_requisitos_tarefa = 0;

  grafo = adicionaVertice(grafo, tarefa1);

  EXPECT_TRUE(grafo->vertices->tarefa->id_tarefa == 100);
  EXPECT_TRUE(strcmp(grafo->vertices->tarefa->nome_tarefa, "primeira tarefa") == 0);  
  EXPECT_TRUE(grafo->vertices->tarefa->tarefa_executada == 0);
  EXPECT_TRUE(grafo->vertices->tarefa->duracao_tarefa == 3);
  EXPECT_TRUE(grafo->vertices->tarefa->inicio_min_tarefa == 0);
  EXPECT_TRUE(grafo->vertices->tarefa->pre_requisitos_tarefa == 0);
  EXPECT_TRUE(grafo->vertices->prox == NULL);


  TpTarefa* tarefa2 = (TpTarefa*)malloc(sizeof(TpTarefa));

  tarefa2->id_tarefa = 102;
  strcpy(tarefa2->nome_tarefa, "segunda tarefa");
  tarefa2->tarefa_executada = 1;
  tarefa2->duracao_tarefa = 2;
  tarefa2->inicio_min_tarefa = 3;
  tarefa2->pre_requisitos_tarefa = 1;
  tarefa2->requisitos = (int*)malloc(2*sizeof(int));
  tarefa2->requisitos[0] = 100;


  grafo = adicionaVertice(grafo, tarefa2);

  EXPECT_TRUE(grafo->vertices->prox->tarefa->id_tarefa == 102);
  EXPECT_TRUE(strcmp(grafo->vertices->prox->tarefa->nome_tarefa, "segunda tarefa") == 0);  
  EXPECT_TRUE(grafo->vertices->prox->tarefa->tarefa_executada == 1);
  EXPECT_TRUE(grafo->vertices->prox->tarefa->duracao_tarefa == 2);
  EXPECT_TRUE(grafo->vertices->prox->tarefa->inicio_min_tarefa == 3);
  EXPECT_TRUE(grafo->vertices->prox->tarefa->pre_requisitos_tarefa == 1);
  EXPECT_TRUE(grafo->vertices->prox->tarefa->requisitos[0] == 100);
  EXPECT_TRUE(grafo->vertices->prox->prox == NULL);


  TpTarefa* tarefa3 = (TpTarefa*)malloc(sizeof(TpTarefa));

  tarefa3->id_tarefa = 102;
  strcpy(tarefa3->nome_tarefa, "terceira tarefa");
  tarefa3->tarefa_executada = 2;
  tarefa3->duracao_tarefa = 3;
  tarefa3->inicio_min_tarefa = 4;
  tarefa3->pre_requisitos_tarefa = 1;
  tarefa3->requisitos = (int*)malloc(2*sizeof(int));
  tarefa3->requisitos[0] = 100;

  grafo = adicionaVertice(grafo, tarefa3);

  EXPECT_EQ(grafo->vertices->prox->tarefa->id_tarefa,102);
  EXPECT_TRUE(strcmp(grafo->vertices->prox->tarefa->nome_tarefa, "segunda tarefa") == 0);  
  EXPECT_EQ(grafo->vertices->prox->tarefa->tarefa_executada, 1);
  EXPECT_EQ(grafo->vertices->prox->tarefa->duracao_tarefa, 2);
  EXPECT_EQ(grafo->vertices->prox->tarefa->inicio_min_tarefa, 3);
  EXPECT_EQ(grafo->vertices->prox->tarefa->pre_requisitos_tarefa, 1);
  EXPECT_EQ(grafo->vertices->prox->tarefa->requisitos[0], 100);
  EXPECT_TRUE(grafo->vertices->prox->prox == NULL);
  
  
}


/*
  Testa função de leitor
  
  Le o grafo de um arquivo de teste, compara os valores salvos com os valores reais
  verifica se a estrutura nao foi corrompida

*/
TEST(TpGrafo, testaLeitor){

  TpGrafo* grafo = inicializa();
  grafo = leitor(grafo, arquivoTeste);

  EXPECT_TRUE(grafo->vertices->tarefa->id_tarefa == 100);
  EXPECT_TRUE(strcmp(grafo->vertices->tarefa->nome_tarefa, "primeira tarefa") == 0);  
  EXPECT_TRUE(grafo->vertices->tarefa->tarefa_executada == 0);
  EXPECT_TRUE(grafo->vertices->tarefa->duracao_tarefa == 3);
  EXPECT_TRUE(grafo->vertices->tarefa->inicio_min_tarefa == 0);
  EXPECT_TRUE(grafo->vertices->tarefa->pre_requisitos_tarefa == 0);


  EXPECT_TRUE(grafo->vertices->prox->tarefa->id_tarefa == 102);
  EXPECT_TRUE(strcmp(grafo->vertices->prox->tarefa->nome_tarefa, "segunda tarefa") == 0);  
  EXPECT_TRUE(grafo->vertices->prox->tarefa->tarefa_executada == 0);
  EXPECT_TRUE(grafo->vertices->prox->tarefa->duracao_tarefa == 2);
  EXPECT_TRUE(grafo->vertices->prox->tarefa->inicio_min_tarefa == 3);
  EXPECT_TRUE(grafo->vertices->prox->tarefa->pre_requisitos_tarefa == 2);
  EXPECT_TRUE(grafo->vertices->prox->tarefa->requisitos[0] == 100);
  EXPECT_TRUE(grafo->vertices->prox->tarefa->requisitos[1] == 101);

  EXPECT_TRUE(grafo->vertices->prox->prox == NULL);
  
}

/*
  Testa função add_tarefa_buffer
  
  Cria uma tarefa, e verifica se a função salva ela corretamente na string passada.
*/
TEST(TpGrafo, testaAddTarefaBuffer){

  char buffer[200];
  for(int i = 0; i<(int)(sizeof(buffer)/sizeof(char)); i++)
    buffer[i]= '\0';

  TpTarefa* tarefa1 = (TpTarefa*)malloc(sizeof(TpTarefa));

  tarefa1->id_tarefa = 100;
  strcpy(tarefa1->nome_tarefa, "primeira tarefa");
  tarefa1->tarefa_executada = 0;
  tarefa1->duracao_tarefa = 3;
  tarefa1->inicio_min_tarefa = 0;
  tarefa1->pre_requisitos_tarefa = 0;

  add_Tarefa_Buffer(buffer ,tarefa1);

  EXPECT_STREQ(buffer, "100 primeira tarefa 0 3 0 0\n");
}

/*
  Testa função ImprimeGrafo
  
  Le o grafo do arquivoTeste, e salva ele em um buffer
  Compara se o resultado obtido é igual ao esperado 
*/
TEST(TpGrafo, testaImprimeGrafo){

  char buffer[300];

  TpGrafo* grafo = inicializa();
  grafo = leitor(grafo, arquivoTeste);

  imprimeGrafo(buffer , grafo);
  EXPECT_STREQ(buffer, "100 primeira tarefa 0 3 0 0\n102 segunda tarefa 0 2 3 2 100 101\n");

}

/*
  Testa função removeTarefa
  
  inicializa um grafo
  adicionamos 4 tarefas

  testa remover uma tarefa inezistente
  verifica se a estrutura de dados foi corrompida

  testa remove uma tarefa no meio do grafo
  verifica se foi removida corretamente
  verifica se a estrutura de dados foi corrompida

  testa remove uma tarefa do fim do grafo
  verifica se foi removida corretamente
  verifica se a estrutura de dados foi corrompida

  testa remover a primeira tarefa
  verifica se foi removida corretamente
  verifica se a estrutura de dados foi corrompida

  testa remover de um grafo com apenas 1 elemento
  verifica se foi removida corretamente
  verifica se a estrutura de dados foi corrompida
  
  testa remover de um grafo vazio
  verifica se a estrutura de dados foi corrompida
*/
TEST(TpGrafo, testaRemoveTarefa){

  TpGrafo* grafo = inicializa();
  char buffer[500];

  TpTarefa* tarefa1 = (TpTarefa*)malloc(sizeof(TpTarefa));
  tarefa1->id_tarefa = 100;
  strcpy(tarefa1->nome_tarefa, "tarefa1");
  tarefa1->tarefa_executada = 0;
  tarefa1->duracao_tarefa = 3;
  tarefa1->inicio_min_tarefa = 0;
  tarefa1->pre_requisitos_tarefa = 0;
  grafo = adicionaVertice(grafo, tarefa1);

  TpTarefa* tarefa2 = (TpTarefa*)malloc(sizeof(TpTarefa));
  tarefa2->id_tarefa = 101;
  strcpy(tarefa2->nome_tarefa, "tarefa2");
  tarefa2->tarefa_executada = 0;
  tarefa2->duracao_tarefa = 3;
  tarefa2->inicio_min_tarefa = 0;
  tarefa2->pre_requisitos_tarefa = 0;
  grafo = adicionaVertice(grafo, tarefa2);

  TpTarefa* tarefa3 = (TpTarefa*)malloc(sizeof(TpTarefa));
  tarefa3->id_tarefa = 102;
  strcpy(tarefa3->nome_tarefa, "tarefa3");
  tarefa3->tarefa_executada = 0;
  tarefa3->duracao_tarefa = 3;
  tarefa3->inicio_min_tarefa = 0;
  tarefa3->pre_requisitos_tarefa = 0;
  grafo = adicionaVertice(grafo, tarefa3);

  TpTarefa* tarefa4 = (TpTarefa*)malloc(sizeof(TpTarefa));
  tarefa4->id_tarefa = 103;
  strcpy(tarefa4->nome_tarefa, "tarefa4");
  tarefa4->tarefa_executada = 0;
  tarefa4->duracao_tarefa = 3;
  tarefa4->inicio_min_tarefa = 0;
  tarefa4->pre_requisitos_tarefa = 0;
  grafo = adicionaVertice(grafo, tarefa4);

  imprimeGrafo(buffer , grafo);  
  EXPECT_STREQ(buffer, "100 tarefa1 0 3 0 0\n101 tarefa2 0 3 0 0\n102 tarefa3 0 3 0 0\n103 tarefa4 0 3 0 0\n");

  grafo = removeTarefa(grafo, 105);
  imprimeGrafo(buffer , grafo);  
  EXPECT_STREQ(buffer, "100 tarefa1 0 3 0 0\n101 tarefa2 0 3 0 0\n102 tarefa3 0 3 0 0\n103 tarefa4 0 3 0 0\n");
  EXPECT_TRUE(grafo->vertices->prox->prox->prox->prox == NULL);

  grafo = removeTarefa(grafo, 102);
  imprimeGrafo(buffer , grafo);  
  EXPECT_STREQ(buffer, "100 tarefa1 0 3 0 0\n101 tarefa2 0 3 0 0\n103 tarefa4 0 3 0 0\n");
  EXPECT_TRUE(grafo->vertices->prox->prox->prox == NULL);  

  grafo = removeTarefa(grafo, 103);
  imprimeGrafo(buffer , grafo);  
  EXPECT_STREQ(buffer, "100 tarefa1 0 3 0 0\n101 tarefa2 0 3 0 0\n");
  EXPECT_TRUE(grafo->vertices->prox->prox == NULL);  

  grafo = removeTarefa(grafo, 100);
  imprimeGrafo(buffer , grafo);  
  EXPECT_STREQ(buffer, "101 tarefa2 0 3 0 0\n");
  EXPECT_TRUE(grafo->vertices->prox == NULL);  

  grafo = removeTarefa(grafo, 101);
  imprimeGrafo(buffer , grafo);  
  EXPECT_STREQ(buffer, "");
  EXPECT_TRUE(grafo->vertices == NULL); 

  grafo = removeTarefa(grafo, 101);
  imprimeGrafo(buffer , grafo);  
  EXPECT_STREQ(buffer, "");
  EXPECT_TRUE(grafo->vertices == NULL);  

}

/*
  Testa função salvaTarefa
  
  Cria uma tarefa com nenhum pre requisito
  salva ela em um arquivo
  
  Cria uma tarefa com pelo menos 1 pre requisito
  salva ela em um arquivo

  verifica se as tarefas foram salvas corretamente
*/
TEST(TpGrafo, testaSalvaTarefa){

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
  tarefa2->tarefa_executada = 0;
  tarefa2->duracao_tarefa = 2;
  tarefa2->inicio_min_tarefa = 3;
  tarefa2->pre_requisitos_tarefa = 2;
  tarefa2->requisitos = (int*)malloc(2*sizeof(int));
  tarefa2->requisitos[0] = 100;
  tarefa2->requisitos[1] = 101;

  FILE* file = fopen(arquivoTeste, "w");
  salvaTarefa(file, tarefa1);
  salvaTarefa(file, tarefa2);

  fclose(file);

  TpGrafo* grafo = inicializa();
  grafo = leitor(grafo, arquivoTeste);
  char buffer[300];

  imprimeGrafo(buffer , grafo);  
  EXPECT_STREQ(buffer, "100 primeira tarefa 0 3 0 0\n102 segunda tarefa 0 2 3 2 100 101\n");
 
}

/*
  Testa função salvarEmArquivo
  
  Le as tarefas existentes em um arquivo
  salva elas em um grafo
  sobreescrever o arquivo com os dados obtidos
  verifica se os dados salvos são os esperados
*/
TEST(TpGrafo, testaSalvaEmArquivo){


  TpGrafo* grafo = inicializa();
  grafo = leitor(grafo, arquivoTeste);

  salvarEmArquivo(grafo, arquivoTeste);

  TpGrafo* novo = inicializa();
  novo = leitor(grafo, arquivoTeste);

  char buffer[300];
  imprimeGrafo(buffer , novo);  
  EXPECT_STREQ(buffer, "100 primeira tarefa 0 3 0 0\n102 segunda tarefa 0 2 3 2 100 101\n");
 
}





int main(int argc, char* *argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}