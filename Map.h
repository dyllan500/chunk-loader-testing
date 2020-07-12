#pragma once
#include "Game.h"
#include "Tiles.h"
#include "Player.h"

class Map {

private:
	SDL_Renderer* renderer = NULL;

public:
	Map(SDL_Renderer* ren);

	std::vector<Chunk> loadedchunks;
  std::vector<Chunks> chunks;

  int light_x;
  int light_y;
  void MouseLight(int mouse_x, int mouse_y);

  bool reload;
	void Check_Chunk(Player* player, Tiles* tiles);
	bool Unload_Chunk(int player_chunk_x, int player_chunk_y, Tiles* tiles);
	void Load_Chunk(int player_chunk_x, int player_chunk_y, Tiles* tiles);
  void handle_tree_tops(int x, int y, Uint16 id, bool remove_tree, Player* player);
	void RemoveTile(int mouse_x, int mouse_y, int player_x, int player_y, Tiles* tiles, Player* player);
	void AddTile(int mouse_x, int mouse_y, int player_x, int player_y, Tiles* tiles, Player* player);
  bool Check_Collision(char dir, int player_x, int player_y, Tiles* tiles);
	void Render(Player* player, Tiles* tiles);
  void Init();
	static bool Match(Chunk m1, Chunk m2);

};
