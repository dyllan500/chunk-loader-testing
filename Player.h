#pragma once
#include "Game.h"
#include "SDL.h"


class Player {

private:
  SDL_Renderer* renderer;

public:
  Player(int player_x, int player_y, int player_h, int player_w, SDL_Texture *tiles, SDL_Renderer *renderer);
  std::vector<Inventory> intventory;
  int x,y,h,w,posx,posy;
  int selected;
  SDL_Texture *sprite;
  void Render();
  void AddItemtoInventory(Uint16 id);
  void RemoveItemtoInventory(Uint16 id);
};
