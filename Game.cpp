#include "Game.h"
#include "TexturesManger.h"
#include "Map.h"
//#include "TextureManager.h"
//#include "GameObject.h"


//GameObject* Player;
//GameObject* Enemy;
//GameObject* Drow;

SDL_Texture *plays;
SDL_Texture *background;
Sprites* sprites;
Player* player;
Map* map;


Game::Game() {


}

Game::~Game() {



}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!... " << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Created! " << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			std::cout << "Renderer Created! " << std::endl;
		}
		isRunning = true;
	}

	TextureManager Texture;

	Sprites sprites;
	sprites.grass = Texture.LoadTexture("grass.png", renderer);
	sprites.rock = Texture.LoadTexture("rock.png", renderer);
	

	plays = Texture.LoadTexture("player.png", renderer);


	
	background = Texture.LoadTexture("back.png", renderer);

	

	map = new Map(renderer);
}

void Game::handleEvents() {
	std::cout << "Event" << std::endl;
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		std::cout << "Quitting";
		break;
	}


}

void Game::update()
{
	movey = movey + 2;
	movex = movex + 1;
	std::cout << "Update" << std::endl;
}

void Game::render() {
	std::cout << "Rendered";
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	std::cout << "Render" << std::endl;
	
	map->Render(player, sprites);
	SDL_Rect player_rect = { WIDTH / 2, HEIGHT / 2, 32, 32 };
	SDL_Rect rect_chunks = { 0, 0, 32, 32 };
	SDL_RenderCopy(renderer, plays, &rect_chunks, &player_rect);
	SDL_RenderPresent(renderer);

	std::cout << "Render" << std::endl;
}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!!! " << std::endl;

}