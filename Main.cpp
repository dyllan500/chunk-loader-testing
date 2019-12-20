#include "Game.h"
#include "Map.h"
#include "TexturesManger.h"
#include "Sprites.h"
#include "Player.h"



int main(int agrc, char *agrv[])
{
	Game *game;
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
