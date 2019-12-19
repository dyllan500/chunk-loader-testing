#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include <random>



const int WIDTH = 1080, HEIGHT = 720, TILE_AMOUNT_X = 100, TILE_AMOUNT_Y = 100, CHUNK_AMOUNT_X = 10, CHUNK_AMOUNT_Y = 10, TILE_WIDTH = 16, TILE_HEIGHT = 16;

typedef struct {
	int x, y, w, h, posx, posy, posw, posh;
} Player;

typedef struct {
	int x, y;
	SDL_Texture *sprite;
} Tile;

typedef struct {
	int x, y;
	std::vector<Tile> tiles;
} Chunk;

typedef struct {
	SDL_Texture *grass;
	SDL_Texture *rock;
}Sprites;



class Game {

	double cnt = 0;
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer *renderer;


public:
	Game();
	~Game();

	int movex = 0;
	int movey = 0;

	void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }


};
