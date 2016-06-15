#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <SDL/SDL_ttf.h>
#include "leitor.h"


TTF_Font* my_font;
#define FONTSIZE 18

void desenha_texto(char* texto, SDL_Surface* dst, int x, int y){
  SDL_Color cor = {255, 255, 0}; //vermelho
  SDL_Surface* src = TTF_RenderText_Blended(my_font, texto, cor);
  SDL_Rect dst_rect = {x, y, 0, 0};
  
  SDL_BlitSurface(src, NULL, dst, &dst_rect);
  
  SDL_FreeSurface(src);
}


void add_Tarefa_Buffer(char* buffer, TpTarefa* tarefa){
  int i;
  char auxiliar[100];
  
  sprintf(auxiliar, "%d %s %d %d %d %d", tarefa->id_tarefa, tarefa->nome_tarefa, tarefa->tarefa_executada, 
  tarefa->duracao_tarefa, tarefa->inicio_min_tarefa, tarefa->pre_requisitos_tarefa);

  strcat(buffer, auxiliar);
  
  for (i = 0; i < tarefa->pre_requisitos_tarefa; i++){
    
    sprintf(auxiliar, " %d", tarefa->requisitos[i]);
    strcat(buffer, auxiliar);
  }

  sprintf(auxiliar, "\n");
  strcat(buffer, auxiliar);

}

void imprimeGrafo(char* buffer, TpGrafo* grafo){

	if(grafo->vertices == NULL){
	}else{
		TpVertice* aux = grafo->vertices;
		char auxiliar[200];

		sprintf(auxiliar, "%d %s %d %d %d %d", aux->tarefa->id_tarefa, aux->tarefa->nome_tarefa, aux->tarefa->tarefa_executada, aux->
		tarefa->duracao_tarefa, aux->tarefa->inicio_min_tarefa, aux->tarefa->pre_requisitos_tarefa);

		strcpy(buffer, auxiliar);

		for (int i = 0; i < aux->tarefa->pre_requisitos_tarefa; i++){
			sprintf(auxiliar, " %d", aux->tarefa->requisitos[i]);
			strcat(buffer, auxiliar);
		}

		sprintf(auxiliar, "\n");
		strcat(buffer, auxiliar);
		aux = aux->prox;

		while(aux!= NULL){  
			add_Tarefa_Buffer(buffer, aux->tarefa);
			aux = aux->prox;
		}
	}
}



int Is_on(SDL_Rect Destino, int largura, int altura, int x, int y){
	if( (x <= (Destino.x + largura)) && (x > Destino.x ) && ( y <= (Destino.y + altura ) ) && (y > Destino.y) )
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}
void Renderiza(SDL_Surface* botao,SDL_Surface*  screen, SDL_Rect Destino){
  SDL_BlitSurface(botao, NULL, screen, &Destino);
}
SDL_Rect set_button_position(SDL_Rect botao, int x , int y){
  botao.x = x;
  botao.y =y;

  return botao;
}

int main(){
  int aux;
  TpGrafo* grafo;
  char tecla;

  grafo = inicializa();
  
  grafo = leitor(grafo);


  salvarEmArquivo(grafo);

  SDL_Surface * screen; // A janela principal

  SDL_Surface *botao_adicionar_desativado, *botao_adicionar_ativado, *botao_remover_desativado, *botao_remover_ativado, *botao_editar_desativado, 
  *botao_editar_ativado, *botao_sair_desativado, *botao_sair_ativado, *background, *easter_egg, *botao_show_ativado, *botao_show_desativado;

  SDL_Rect destino_botao_remover, destino_botao_adicionar,destino_botao_editar,destino_botao_sair,destino_botao_editarack,destino_mito, destino_botao_show;
  SDL_Event event;
  int x,y;

  destino_botao_remover = set_button_position(destino_botao_remover, 280,170);
  destino_botao_adicionar = set_button_position(destino_botao_adicionar, 280,220);
  destino_botao_editar =  set_button_position(destino_botao_editar,280, 270);
  destino_botao_show = set_button_position(destino_botao_show,280, 320);
  destino_botao_sair = set_button_position(destino_botao_sair,280, 370);

  destino_mito = set_button_position(destino_mito,0,0);



  SDL_Init(SDL_INIT_VIDEO); // Inicializa o SDL e o sistema de vídeo  
   
  if(TTF_Init() == -1)
    return -1;

  screen = SDL_SetVideoMode(700, 431, 16, SDL_SWSURFACE); // Cria a janela

  my_font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf", FONTSIZE);
  botao_remover_desativado = SDL_LoadBMP("imagens/botoes/rmv_ye.bmp"); // Carrega a imagem no formato BMP
  botao_adicionar_desativado =SDL_LoadBMP("imagens/botoes/add_ye.bmp");
  botao_editar_desativado= SDL_LoadBMP("imagens/botoes/edit_ye.bmp");
  botao_sair_desativado =SDL_LoadBMP("imagens/botoes/quit_ye.bmp");
  botao_show_desativado =SDL_LoadBMP("imagens/botoes/show_ye.bmp");


  background =SDL_LoadBMP("imagens/fundo/background.bmp");
  easter_egg =SDL_LoadBMP("imagens/botoes/mito.bmp");

  botao_remover_ativado =SDL_LoadBMP("imagens/botoes/rmv_gr.bmp");
  botao_adicionar_ativado =SDL_LoadBMP("imagens/botoes/add_gr.bmp");
  botao_editar_ativado =SDL_LoadBMP("imagens/botoes/edit_gr.bmp");
  botao_sair_ativado =SDL_LoadBMP("imagens/botoes/quit_gr.bmp");
  botao_show_ativado =SDL_LoadBMP("imagens/botoes/show_gr.bmp");

  // Verifica se carregou a imagem
  if (botao_remover_desativado == NULL || botao_editar_desativado == NULL || botao_editar_desativado == NULL || botao_sair_desativado == NULL ){
     printf("Não foi possivel abrir imagem\n");
     return 1;
  }

  int done = 0; // Variável de controle do loop
  while (done == 0) {// Enquanto não concluir{
  	
  	while(SDL_PollEvent(&event)){// loop de eventos
   		x = event.button.x;
  		y = event.button.y;

    	if (event.type == SDL_QUIT){
    		done = 1;
    	}

      if (event.type == SDL_MOUSEBUTTONDOWN && (! Is_on(destino_botao_sair, 150,36,x,y))  ) {// Se o usuário clicou
          done = 1;
      }


       if (event.type == SDL_MOUSEBUTTONDOWN && (! Is_on(destino_botao_remover, 150,36,x,y))  ) {// Se o usuário clicou
          
       }
       if ( event.type == SDL_MOUSEBUTTONDOWN && (! Is_on(destino_botao_show, 150,36,x,y))  ) {// Se o usuário clicou
          	char buffer[10000];
           
        	imprimeGrafo(buffer, grafo);
        	printf("%s\n", buffer );

        	initscr();
        	keypad(stdscr, true);
        	printw("%s\n", buffer);
        	do{
        		tecla = getch();
        	}while(tecla != 10);


        }      

        SDL_Flip(screen);

	} 
 	SDL_FillRect(screen,NULL,0x0);
 	SDL_BlitSurface(background, NULL, screen, &destino_botao_editarack);
  	
 	if(!Is_on(destino_botao_remover, 150,36,x,y) )
    Renderiza(botao_remover_desativado,screen,destino_botao_remover);
 	else
    Renderiza(botao_remover_ativado,screen,destino_botao_remover);

	if(!Is_on(destino_botao_adicionar, 150,36,x,y))
    Renderiza(botao_adicionar_desativado,screen,destino_botao_adicionar);
 	else
    Renderiza(botao_adicionar_ativado,screen,destino_botao_adicionar);
  	

	if(!Is_on(destino_botao_editar, 150,36,x,y) )
	   Renderiza(botao_editar_desativado,screen,destino_botao_editar);
  else
     Renderiza(botao_editar_ativado,screen,destino_botao_editar);

 
  if(!Is_on(destino_botao_sair, 150,36,x,y) )
     Renderiza(botao_sair_desativado,screen,destino_botao_sair);
  else
     Renderiza(botao_sair_ativado,screen,destino_botao_sair);

    if(!Is_on(destino_botao_show, 150,36,x,y) )
     Renderiza(botao_show_desativado,screen,destino_botao_show);
  else
     Renderiza(botao_show_ativado,screen,destino_botao_show);


  if(x <= 10 && x >0 && y <= 431 && y > 425)
     Renderiza(easter_egg,screen,destino_mito);


  SDL_UpdateRect(screen,0,0,0,0);
  SDL_Delay(60);
}
TTF_Quit();

SDL_Quit();

  return 0;
} 


