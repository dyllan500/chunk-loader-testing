#include "Game.h"
#include "TexturesManger.h"
#include "Map.h"
#include "Tiles.h"
#include "Item.h"
#include "Player.h"
#include "SDL_ttf.h"
#include <string>

SDL_Texture *plays;
SDL_Texture *background;
SDL_Texture *stone_ui;
SDL_Texture *grass_ui;
SDL_Texture *tree_o_ui;
SDL_Texture *tree_t_ui;
SDL_Texture *tree_th_ui;
SDL_Texture *tree_f_ui;
SDL_Texture *tree_fi_ui;
SDL_Texture *tree_s_ui;
SDL_Texture *tree_top_ui;
SDL_Texture *dirt_ui;
Tiles *tiles;
Items *items;
Player *player;
Map *map;
Uint8 KEYS[MAX_KEYS];
bool picking;
bool placing;
int last_tic;
int angle;
TTF_Font* Sans;
SDL_Color White;
SDL_Surface* surfaceMessage;
SDL_Texture* Message;

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
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		isRunning = true;
	}
	if (TTF_Init() < 0) {
    // Error handling code
  }

  for(int i = 0; i < MAX_KEYS; i++) {
    KEYS[i] = BUTTON_NONE;
  }
  //SDL_EnableKeyRepeat(0,0);
  angle = 0;
  picking = false;
  placing = false;
	TextureManager Texture;
	player = new Player(WIDTH/2, HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT, Texture.LoadTexture("player.png", renderer), renderer);
	tiles = new Tiles();
	items = new Items();
	tiles->grass = Texture.LoadTexture("grass.png", renderer);
	tiles->dirt = Texture.LoadTexture("dirt.png", renderer);
	tiles->stone = Texture.LoadTexture("rock.png", renderer);
	tiles->fade = Texture.LoadTexture("fade-out.png", renderer);
	tiles->sappling = Texture.LoadTexture("sappling.png", renderer);
	tiles->inventoryUI = Texture.LoadTexture("Hotbar32x32.png", renderer);
	grass_ui = Texture.LoadTexture("grass.png", renderer);
	dirt_ui = Texture.LoadTexture("dirt.png", renderer);
	stone_ui = Texture.LoadTexture("rock.png", renderer);
	plays = Texture.LoadTexture("player.png", renderer);
	background = Texture.LoadTexture("back.png", renderer);

	tiles->tree_o = Texture.LoadTexture("wood.png", renderer);
	tiles->tree_t = Texture.LoadTexture("wood1.png", renderer);
	tiles->tree_th = Texture.LoadTexture("wood2.png", renderer);
	tiles->tree_f = Texture.LoadTexture("wood3.png", renderer);
	tiles->tree_fi = Texture.LoadTexture("wood4.png", renderer);
	tiles->tree_s = Texture.LoadTexture("wood5.png", renderer);

	tiles->tree_top = Texture.LoadTexture("tree_top.png", renderer);

	tree_o_ui = Texture.LoadTexture("wood.png", renderer);
	tree_t_ui = Texture.LoadTexture("wood1.png", renderer);
	tree_th_ui = Texture.LoadTexture("wood2.png", renderer);
	tree_f_ui = Texture.LoadTexture("wood3.png", renderer);
	tree_fi_ui = Texture.LoadTexture("wood4.png", renderer);
	tree_s_ui = Texture.LoadTexture("wood5.png", renderer);

	tree_top_ui = Texture.LoadTexture("tree_top.png", renderer);

	items->pickax = Texture.LoadTexture("pickaxe.png", renderer);
	items->ax = Texture.LoadTexture("ax.png", renderer);

  player->posx = 10;
  player->posy = -10;
  Uint16 id = 3;
  player->intventory.push_back({id, 100});
  id = 4;
  player->intventory.push_back({id, 100});
  id = 6;
  player->intventory.push_back({id, 100});
  id = 7;
  player->intventory.push_back({id, 100});
  id = 8;
  player->intventory.push_back({id, 100});
  id = Tree_Top;
  player->intventory.push_back({id, 100});
  Sans = TTF_OpenFont("Sans.ttf", 16);
  if (Sans == NULL){

  }
  White = {255, 255, 255};

	map = new Map(renderer);
}

void Game::handleEvents(SDL_Event* event) {
	switch (event->type) {
	case SDL_QUIT:
		isRunning = false;
		break;
  case SDL_KEYDOWN:
    KEYS[event->key.keysym.sym] = BUTTON_DOWN;
    break;
  case SDL_KEYUP:
    KEYS[event->key.keysym.sym] = BUTTON_UP;
    break;
  case SDL_MOUSEBUTTONDOWN:
    if(event->button.button == SDL_BUTTON_RIGHT){
      picking = true;
    }else if(event->button.button == SDL_BUTTON_LEFT){
      placing = true;
    }
    break;
  case SDL_MOUSEMOTION:
    if (picking){
      map->RemoveTile(event->motion.x, event->motion.y, player->posx, player->posy, tiles, player);
    }
    if (placing){
      map->AddTile(event->motion.x, event->motion.y, player->posx, player->posy, tiles, player);
    }
    map->MouseLight(event->motion.x, event->motion.y);
    break;
	default:
	  picking = false;
	  placing = false;
		break;
	}
  handleKeys();
}

void Game::handleKeys() {
    if(KEYS[SDLK_s] == BUTTON_DOWN) {
      if(!map->Check_Collision('s', player->posx, player->posy, tiles)) {
        player->posy = player->posy + 1;
      }
    }
    if (KEYS[SDLK_s] == BUTTON_UP)
    {
        KEYS[SDLK_s] = BUTTON_NONE;
    }
    if(KEYS[SDLK_w] == BUTTON_DOWN) {
        if(!map->Check_Collision('n', player->posx, player->posy, tiles)) {
            player->posy = player->posy - 1;
        }
    }
    if(KEYS[SDLK_d] == BUTTON_DOWN) {
        if(!map->Check_Collision('e', player->posx, player->posy, tiles)) {
            player->posx = player->posx + 1;
       }
    }
    if(KEYS[SDLK_a] == BUTTON_DOWN) {
        if(!map->Check_Collision('w', player->posx, player->posy, tiles)) {
            player->posx = player->posx - 1;
        }
    }
    if(KEYS[SDLK_ESCAPE]) {
        isRunning = false;
    }
    if(KEYS[SDLK_SPACE] == BUTTON_DOWN){
      if(!map->Check_Collision('n', player->posx, player->posy, tiles)) {
            player->posy = player->posy - 2;
        }
    }
    if(KEYS[SDLK_8]){
      player->selected = 7;
    }
    if(KEYS[SDLK_7]){
      player->selected = 6;
    }
    if(KEYS[SDLK_6]){
      player->selected = 5;
    }
    if(KEYS[SDLK_5]){
      player->selected = 4;
    }
    if(KEYS[SDLK_4]){
      player->selected = 3;
    }
    if(KEYS[SDLK_3]){
      player->selected = 2;
    }
    if(KEYS[SDLK_2]){
      player->selected = 1;
    }
    if(KEYS[SDLK_1]){
      player->selected = 0;
    }
    /*if(KEYS[SDLK_LCTRL] && KEYS[SDLK_PLUS]){
      PIXEL_SIZE = PIXEL_SIZE + .1;
    }
    if(KEYS[SDLK_LCTRL] && KEYS[SDLK_MINUS]){
      PIXEL_SIZE = PIXEL_SIZE - .1;
    }*/
}

void Game::update()
{
  if(!map->Check_Collision('s', player->posx, player->posy, tiles)) {
            player->posy = player->posy + 1;
  }
}
//TODO fix player renderereererererer
void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
  map->Render(player, tiles);

	SDL_Rect player_rect = { (WIDTH / 2), (HEIGHT / 2), PLAYER_WIDTH * PIXEL_SIZE, PLAYER_HEIGHT *PIXEL_SIZE};
	SDL_Rect rect_chunks = { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT };
	SDL_RenderCopy(renderer, plays, &rect_chunks, &player_rect);

	SDL_Rect ui_rect = { 0, 0, 360 * PIXEL_SIZE, 240 *PIXEL_SIZE};
	SDL_Rect rect_ui = { 0, 0, 360, 240 };
	SDL_RenderCopy(renderer, tiles->inventoryUI, &rect_ui, &ui_rect);

	SDL_Rect pick_rect = { WIDTH/2+28, HEIGHT/2-16, 32 * PIXEL_SIZE, 32 *PIXEL_SIZE};
	SDL_Rect rect_pick = { 0, 0, 32, 32 };
	SDL_Point center = {0, 30};
	//SDL_RenderCopy_(renderer, items->pickax, &rect_pick, &pick_rect);
	if (picking){
    angle += 10;
    SDL_RenderCopyEx(renderer, items->pickax, &rect_pick, &pick_rect, angle, &center, SDL_FLIP_NONE);
	}else{
    angle = 0;
	}

  //std::cout << player->intventory.size() << std::endl;
  for (int i = 0; i < player->intventory.size(); i++){
    if (player->intventory[i].amount > 0){
    SDL_Rect one_rect = { 25 + (i*42), 40, 16 * PIXEL_SIZE, 16 *PIXEL_SIZE};
    SDL_Rect rect_one = { 0, 0, 16, 16 };
    if (Dirt_block == player->intventory[i].id){
      SDL_RenderCopy(renderer, grass_ui, &rect_one, &one_rect);
    } else if (Stone_block == player->intventory[i].id){
      SDL_RenderCopy(renderer, stone_ui, &rect_one, &one_rect);
    }else if (Tree_Top == player->intventory[i].id){
      SDL_RenderCopy(renderer, tree_top_ui, &rect_one, &one_rect);
    }
    std::string s = std::to_string(player->intventory[i].amount);
    surfaceMessage = TTF_RenderText_Solid(Sans, s.c_str(), White);
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect = {20 + (i*42), 44, 16, 16};
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    }
  }
	SDL_RenderPresent(renderer);
}

void Game::clean() {
  std::cout << "closing" << std::endl;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
