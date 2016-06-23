#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_ttf.h>
#include "operaGrafo.h"
#include "GUI.h"
#include <curses.h>
#include <time.h>

int sair(TpGrafo* grafo){
	salvarEmArquivo(grafo);
	return 1;
}

int main(){
	char tarefas[10000];
	TpGrafo* grafo;
	int button_width = 150, button_height = 36, FONTSIZE = 18,x,y, aux =0;
	TTF_Font* my_font;
	SDL_Surface * screen, *screen2, *botao_adicionar_desativado, *botao_adicionar_ativado, *botao_remover_desativado, *botao_remover_ativado, *botao_editar_desativado, 
	*botao_editar_ativado, *botao_sair_desativado, *botao_sair_ativado, *background, *easter_egg, *botao_show_ativado, *botao_show_desativado;

	SDL_Rect destino_botao_remover, destino_botao_adicionar,destino_botao_editar,destino_botao_sair,destino_botao_editarack,destino_mito, destino_botao_show;
	SDL_Event event;


	grafo = inicializa(); 
	grafo = leitor(grafo, "tarefas");
	salvarEmArquivo(grafo);

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
	SDL_FillRect(screen,NULL,0x0);
	SDL_BlitSurface(background, NULL, screen, &destino_botao_editarack);

	while (done == 0) {// Enquanto não concluir
		while(SDL_PollEvent(&event)){// loop de eventos
			x = event.button.x;
			y = event.button.y;

			if (event.type == SDL_QUIT){
				done = sair(grafo);
			}

			if (event.type == SDL_MOUSEBUTTONDOWN && (! Is_on(destino_botao_sair, button_width,button_height,x,y))  ) {// Se o usuário clicou
				done = sair(grafo);
			}

			if (event.type == SDL_MOUSEBUTTONDOWN && (! Is_on(destino_botao_remover, button_width,button_height,x,y))  ) {// Se o usuário clicou
				int identificador;
				SDL_Quit();

				initscr(); /* Inicio da ncurses*/
				keypad(stdscr, true); /* Esse comando pega todas as teclas*/
				srand(time(NULL));
				start_color(); /*Essa função torna possí­vel o uso das cores*/
				init_pair(1,COLOR_WHITE,COLOR_BLACK); /*Texto(Azul) | Fundo(Branco)*/
				init_pair(2,COLOR_GREEN,COLOR_BLACK); /*Texto(Verde) | Fundo(Preto)*/
				bkgd(COLOR_PAIR(2)); 
				printw("Digite o ID:");

				scanw("%d", &identificador);

				grafo = removeTarefa(grafo, identificador);
				clear();


				endwin();/*Fim da ncurses*/


				SDL_Init(SDL_INIT_VIDEO); // Inicializa o SDL e o sistema de vídeo  

				screen = SDL_SetVideoMode(700, 431, 16, SDL_SWSURFACE); // Cria a janela
				SDL_FillRect(screen,NULL,0x0);
				SDL_BlitSurface(background, NULL, screen, &destino_botao_editarack);
			}


			if (event.type == SDL_MOUSEBUTTONDOWN && (! Is_on(destino_botao_remover, button_width,button_height,x,y))  ) {// Se o usuário clicou

			}

			if ( event.type == SDL_MOUSEBUTTONDOWN && (! Is_on(destino_botao_show, button_width,button_height,x,y))  ) {// Se o usuário clicou
				char* buffer;
				SDL_Quit();
				buffer = (char*) calloc( 10000 , sizeof(char)); 

				imprimeGrafo(buffer, grafo);
				printf("%s\n", buffer );
				strcpy(tarefas, buffer);
				initscr(); /* Inicio da ncurses*/
				//resize_term(800,500);
				keypad(stdscr, true); /* Esse comando pega todas as teclas*/
				srand(time(NULL));
				start_color(); /*Essa função torna possí­vel o uso das cores*/
				init_pair(1,COLOR_WHITE,COLOR_BLACK); /*Texto(Azul) | Fundo(Branco)*/
				init_pair(2,COLOR_GREEN,COLOR_BLACK); /*Texto(Verde) | Fundo(Preto)*/
				bkgd(COLOR_PAIR(2)); 
				printw("tarefas:\n%s ", buffer);

				getch();
				clear();

				endwin();/*Fim da ncurses*/

				SDL_Init(SDL_INIT_VIDEO); // Inicializa o SDL e o sistema de vídeo  

				screen = SDL_SetVideoMode(700, 431, 16, SDL_SWSURFACE); // Cria a janela
				SDL_FillRect(screen,NULL,0x0);
				SDL_BlitSurface(background, NULL, screen, &destino_botao_editarack);

				free(buffer);
			}
		} 

		if(!Is_on(destino_botao_remover, button_width,button_height,x,y) )
			Renderiza(botao_remover_desativado,screen,destino_botao_remover);
		else
			Renderiza(botao_remover_ativado,screen,destino_botao_remover);

		if(!Is_on(destino_botao_adicionar, button_width,button_height,x,y))
			Renderiza(botao_adicionar_desativado,screen,destino_botao_adicionar);
		else
			Renderiza(botao_adicionar_ativado,screen,destino_botao_adicionar);


		if(!Is_on(destino_botao_editar, button_width,button_height,x,y) )
			Renderiza(botao_editar_desativado,screen,destino_botao_editar);
		else
			Renderiza(botao_editar_ativado,screen,destino_botao_editar);


		if(!Is_on(destino_botao_sair, button_width,button_height,x,y) )
			Renderiza(botao_sair_desativado,screen,destino_botao_sair);
		else
			Renderiza(botao_sair_ativado,screen,destino_botao_sair);

		if(!Is_on(destino_botao_show, button_width,button_height,x,y) )
			Renderiza(botao_show_desativado,screen,destino_botao_show);
		else
			Renderiza(botao_show_ativado,screen,destino_botao_show);



		SDL_UpdateRect(screen,0,0,0,0);

		SDL_Delay(60);

	}
	TTF_Quit();

	SDL_Quit(); // Fecha o SDL

	return 0;
}