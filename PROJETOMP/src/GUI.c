#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_ttf.h>
#include "operaGrafo.h"
#include "GUI.h"



void desenha_texto(char* texto, SDL_Surface* dst, int x, int y, TTF_Font* my_font){
  SDL_Color cor = {255, 255, 0}; //vermelho
  SDL_Surface* src = TTF_RenderText_Blended(my_font, texto, cor);
  SDL_Rect dst_rect = {x, y, 0, 0};
  
  SDL_BlitSurface(src, NULL, dst, &dst_rect);
  
  SDL_FreeSurface(src);
}

void Renderiza(SDL_Surface* botao,SDL_Surface*  screen, SDL_Rect Destino){
  SDL_BlitSurface(botao, NULL, screen, &Destino);
}


SDL_Rect set_button_position(SDL_Rect botao, int x , int y){
  botao.x = x;
  botao.y =y;

  return botao;
}


int Is_on(SDL_Rect Destino, int largura, int altura, int x, int y){
  if( (x <= (Destino.x + largura)) && (x > Destino.x ) && ( y <= (Destino.y + altura ) ) && (y > Destino.y) )
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}


