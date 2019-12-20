#include "Player.h"
#include "Game.h"

  Player::Player(int player_x, int player_y, int player_h, int player_w, SDL_Texture *sprites, SDL_Renderer* ren)
	{
		int x = player_x;
		int y = player_y;
		int h = player_h;
		int w = player_w;
		int posx = player_x;
		int posy = player_y;
    SDL_Texture *sprite = sprites;
    SDL_Renderer *renderer = ren;
	}

  void Player::Render()
	{
    SDL_Rect rect_chunk = { x, y, w, h };
    SDL_Rect rect_chunks = { 0, 0, 16, 16 };
    SDL_RenderCopy(renderer, sprite, &rect_chunks, &rect_chunk);
	}
