#pragma once
#include "Game.h"


class Map {

private:
	SDL_Renderer* renderer = NULL;

public:
	Map(SDL_Renderer* ren);

	std::vector<Chunk> loadedchunks;

	void Check_Chunk(Player* player, Sprites* sprites);
	

	void Unload_Chunk(int player_chunk_x, int player_chunk_y);
	

	void Load_Chunk(int player_chunk_x, int player_chunk_y, Sprites* sprites);

	void Render(Player* player, Sprites* sprites);

	static bool Match(Chunk m1, Chunk m2);

};
