#include "Game.h"
#include "Map.h"
#include "TexturesManger.h"



int main(int agrc, char *agrv[])
{
	Game *game;
	


	Player player;
	player.x = WIDTH / 2;
	player.y = HEIGHT / 2;
	player.h = 16;
	player.w = 16;
	player.posx = player.x;
	player.posy = player.y;
	player.posh = player.h;
	player.posw = player.w;




	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("Game Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();
		
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		std::cout << "Looping" << std::endl;
	}

	game->clean();
	return EXIT_SUCCESS;
}
