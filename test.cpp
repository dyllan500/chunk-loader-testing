#include "SDL2/SDL.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "SDL2/SDL_image.h"
#include <random>

const int WIDTH = 1080, HEIGHT = 720, TILE_AMOUNT_X = 100, TILE_AMOUNT_Y = 100, CHUNK_AMOUNT_X = 10, CHUNK_AMOUNT_Y = 10, TILE_WIDTH = 16, TILE_HEIGHT = 16;

typedef struct{
    int x, y, w, h, posx, posy, posw, posh;
} Player;

typedef struct{
  int x, y;
  SDL_Texture *sprite;
} Tile;

typedef struct{
  int x, y;
  std::vector<Tile> tiles;
} Chunk;

typedef struct{
  SDL_Texture *grass;
  SDL_Texture *rock;
}Sprites;

bool Match(Chunk m1, Chunk m2){
    return m1.x == m2.x && m1.y == m2.y;
}

class Map{
  public:

  std::vector<Chunk> loadedchunks;

  void Check_Chunk(Player player, Sprites sprites){
    int player_chunk_x = player.posx / TILE_AMOUNT_X;
    int player_chunk_y = player.posy / TILE_AMOUNT_Y;
    Unload_Chunk(player_chunk_x, player_chunk_y);
    Load_Chunk(player_chunk_x, player_chunk_y, sprites);
  }

  void Unload_Chunk(int player_chunk_x, int player_chunk_y){
    int i = 0;
    for (Chunk chunk : loadedchunks){
      if (chunk.x > player_chunk_x+(CHUNK_AMOUNT_X-1)/2 || chunk.x < player_chunk_x-(CHUNK_AMOUNT_X-1)/2 || chunk.y > player_chunk_y+(CHUNK_AMOUNT_Y-1)/2 || chunk.y < player_chunk_y-(CHUNK_AMOUNT_Y-1)/2){
        std::cout << "unload" << std::endl;
        loadedchunks.erase(loadedchunks.begin()+i);
        i++;
      }
    }
  }

  void Load_Chunk(int player_chunk_x, int player_chunk_y, Sprites sprites){
    for (int i = player_chunk_x - (CHUNK_AMOUNT_X-1)/2; i <= player_chunk_x + (CHUNK_AMOUNT_X-1)/2; i++){
      for (int j = player_chunk_y - (CHUNK_AMOUNT_Y-1)/2; j <= player_chunk_y + (CHUNK_AMOUNT_Y-1)/2; j++){
        Chunk chunk;
        chunk.x = i;
        chunk.y = j;
        std::vector<Chunk> test;
        test.push_back(chunk);
        if (std::search(loadedchunks.begin(), loadedchunks.end(), test.begin(), test.end(), Match) == loadedchunks.end()){
          std::cout << "load" << std::endl;
          for (int x = 0; x < TILE_AMOUNT_X; x++){
            for (int y = 0; y < TILE_AMOUNT_Y; y++){
              Tile tile;
              tile.x = x;
              tile.y = y;
              int dice = rand()%100;
              if(dice%2 == 0){
                tile.sprite = sprites.grass;
              }
              else{
                tile.sprite = sprites.rock;
              }

              chunk.tiles.push_back(tile);
            }
          }
          loadedchunks.push_back(chunk);
        }
      }
    }
  }
};

int main( int agrc, char *agrv[])
{
  SDL_Renderer *renderer = NULL;
  SDL_Window *window = NULL;
  Player player;
  player.x = WIDTH/2;
  player.y = HEIGHT/2;
  player.h = 16;
  player.w = 16;
  player.posx = player.x;
  player.posy = player.y;
  player.posh = player.h;
  player.posw = player.w;
  Map map;

  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  IMG_Init(IMG_INIT_JPG);

  window = SDL_CreateWindow("Ello!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
  renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_Event windowEvent;

  SDL_Surface *grassa = NULL;
  SDL_Texture *ground = NULL;
  grassa = IMG_Load("grass.png");
  ground = SDL_CreateTextureFromSurface(renderer, grassa);
  SDL_FreeSurface(grassa);

  SDL_Surface *rock = NULL;
  SDL_Texture *rockk = NULL;
  rock = IMG_Load("rock.png");
  rockk = SDL_CreateTextureFromSurface(renderer, rock);
  SDL_FreeSurface(rock);

  Sprites sprites;
  sprites.grass = ground;
  sprites.rock = rockk;
  SDL_Surface *play = NULL;
  SDL_Texture *plays = NULL;
  play = IMG_Load("player.png");
  plays = SDL_CreateTextureFromSurface(renderer, play);
  SDL_FreeSurface(play);
  while (true)
    {
      if (SDL_PollEvent( &windowEvent))
        {
          if(SDL_QUIT == windowEvent.type)
            {
              break;

            }
          if(SDLK_d == windowEvent.type){
            player.posx = player.posx + 1;
          }
        }
      SDL_RenderClear(renderer);
      map.Check_Chunk(player, sprites);
      for (Chunk chunk : map.loadedchunks){
          for (Tile tile : chunk.tiles){
            SDL_Rect rect_chunk = {tile.x*16+chunk.x*TILE_AMOUNT_X*TILE_WIDTH - player.posx*TILE_WIDTH - TILE_WIDTH - WIDTH/2, tile.y*16+chunk.y*TILE_AMOUNT_Y*TILE_HEIGHT - player.posy*TILE_HEIGHT - TILE_HEIGHT - HEIGHT/2, 16, 16};
            SDL_Rect rect_chunks = {0, 0, 16, 16};
            SDL_RenderCopy(renderer, tile.sprite, &rect_chunks, &rect_chunk);
          }
      }
      SDL_Rect rect_chunk = {WIDTH/2, HEIGHT/2, 16, 16};
      SDL_Rect rect_chunks = {0, 0, 32, 32};
      SDL_RenderCopy(renderer, plays, &rect_chunks, &rect_chunk);
      SDL_RenderPresent(renderer);
      player.posx = player.posx + 1;
      std::cout << player.posx << std::endl;
    }
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  return EXIT_SUCCESS;
}
