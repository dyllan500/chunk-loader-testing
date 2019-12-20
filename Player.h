#pragma once
#include "Game.h"
#include "SDL.h"


class Player {

private:
  SDL_Renderer* renderer;

public:
  Player(int player_x, int player_y, int player_h, int player_w, SDL_Texture *sprites, SDL_Renderer *renderer);
  int x,y,h,w,posx,posy;
  SDL_Texture *sprite;
  void Render();
};
