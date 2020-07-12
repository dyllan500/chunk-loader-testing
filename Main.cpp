#include "Game.h"
#include "Map.h"
#include "TexturesManger.h"
#include "Tiles.h"
#include "Player.h"

int main(int agrc, char *agrv[])
{
  std::vector<Chunks> chunks;
  std::vector<Tile_ID> temp_ids;
  for (int16_t x = 0; x < CHUNK_SIZE_X; x++){
    for (int16_t y = 0; y < CHUNK_SIZE_Y; y++){
      for (int16_t i = 0; i < TILE_AMOUNT_X; i++){
        for (int16_t j = 0; j < TILE_AMOUNT_Y; j++){
          if (y != 0){
            if (i <= 0 || j <= 0){
            temp_ids.push_back({0,0,true,Grass});
            }else{
            temp_ids.push_back({0,0,true,Stone});
            }
          }
          else{
            temp_ids.push_back({0,0,false,NONE});
          }

        }
      }
    chunks.push_back({x, y, temp_ids});
    temp_ids.erase(temp_ids.begin(), temp_ids.end());
    }
  }
  FILE *fptr;
  fptr = fopen("map1.dat","wb");
  fwrite(&chunks, sizeof(chunks), 1, fptr);
  fclose(fptr);


	Game *game;
	const int FPS = 244;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("Game Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
	while (game->running())
	{
	  SDL_Event event;
		frameStart = SDL_GetTicks();
		while(SDL_PollEvent(&event) != 0)
    {
      game->handleEvents(&event);
    }
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return EXIT_SUCCESS;
}
