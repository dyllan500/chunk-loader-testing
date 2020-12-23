#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include <random>
#include <string>

const int WIDTH = 1080, HEIGHT = 720, TILE_AMOUNT_X = 10, TILE_AMOUNT_Y = 10, CHUNK_AMOUNT_X = 10, CHUNK_AMOUNT_Y = 6, TILE_WIDTH = 16, TILE_HEIGHT = 16, MAX_KEYS = 322;
const int CHUNK_SIZE_X = 840, CHUNK_SIZE_Y = 240; //840 240
const int PLAYER_WIDTH = 32, PLAYER_HEIGHT = 48;
const float PIXEL_SIZE = 1.0;
#define BUTTON_NONE 0
#define BUTTON_DOWN 1
#define BUTTON_UP 2

typedef struct {
	int x, y;
	float time;
	bool collision;
	int16_t sprite_x, sprite_y;
	SDL_Texture *sprite;
} Tile;

typedef struct {
	int x, y;
	std::vector<Tile> tiles;
} Chunk;

typedef struct {
  int16_t x;
  int16_t y;
  bool collision;
  int16_t type;
  int16_t item;
} Tile_ID;

typedef struct {
  int16_t x;
  int16_t y;
  std::vector<Tile_ID> tile_ids;
} Chunks;

typedef struct {
  int16_t id;
  int16_t amount;
} Inventory;

enum TILES {
  NONE = Uint16(0),
  Grass = Uint16(1),
  Dirt = Uint16(2),
  Stone = Uint16(3),
  Tree = Uint16(4),
  Tree_Top = Uint16(5),
  Sappling = Uint16(6),
  };

enum ITEMS {
  NOTHING = Uint16(0),
  Dirt_block = Uint16(1),
  Stone_block = Uint16(2),
  Wood_block = Uint16(3),
  Stone_Pickax = Uint16(4),
  Stone_Ax = Uint16(5)
  };

class Game {

	double cnt = 0;
	bool isRunning;
	int mouse_x, mouse_y;
	SDL_Window *window;
	SDL_Renderer *renderer;


public:
	Game();
	~Game();
	int movex = 0;
	int movey = 0;

	void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents(SDL_Event* event);
	void handleKeys();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }


};
