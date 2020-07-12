#include "Player.h"
#include "Game.h"
#include <algorithm>

  Player::Player(int player_x, int player_y, int player_h, int player_w, SDL_Texture *tiles, SDL_Renderer* ren)
	{
		int x = player_x;
		int y = player_y;
		int h = player_h;
		int w = player_w;
		int posx = player_x;
		int posy = player_y;
    SDL_Texture *sprite = tiles;
    SDL_Renderer *renderer = ren;
    std::vector<Inventory> intventory;
    int selected = 0;
	}

	void Player::AddItemtoInventory(Uint16 id){
    int i = 0;
    int remove_here = -1;
    bool once = true;
    bool inventory_contains = false;
    for (Inventory item : intventory){
      if (id == item.id && item.amount > 0){
        intventory[i].amount ++;
        inventory_contains = true;
      }
      if (item.amount <= 0 && once){
        remove_here = i;
        once = false;
      }
      i++;
    }
    if (!inventory_contains && intventory.size()){
      if (remove_here >= 0){
       intventory[remove_here].id = id;
       intventory[remove_here].amount ++;
      }else{
        intventory.push_back({id, 1});
      }
    }
    if (intventory.size() == 0){
      intventory.push_back({id, 1});
    }
	}

	void Player::RemoveItemtoInventory(Uint16 id){
    int i = 0;
    int remove_here = 0;
    bool inventory_contains = false;
    for (Inventory item : intventory){
      if (id == item.id && item.amount > 0){
        intventory[i].amount --;
        inventory_contains = true;
        remove_here = i;
      }
      i++;
    }
	}

  void Player::Render()
	{
    SDL_Rect rect_chunk = { x*PIXEL_SIZE, y*PIXEL_SIZE, w*PIXEL_SIZE, h*PIXEL_SIZE };
    SDL_Rect rect_chunks = { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT };
    SDL_RenderCopy(renderer, sprite, &rect_chunks, &rect_chunk);
	}
