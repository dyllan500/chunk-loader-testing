#include "Map.h"



	Map::Map(SDL_Renderer* ren)
	{
		renderer = ren;
		std::vector<Chunk> loadedchunks;
	}

	bool Map::Match(Chunk m1, Chunk m2) {
		return m1.x == m2.x && m1.y == m2.y;
	}

	void Map::Check_Chunk(Player* player, Sprites* sprites) {
		int player_chunk_x = player->posx / TILE_AMOUNT_X;
		int player_chunk_y = player->posy / TILE_AMOUNT_Y;
		Unload_Chunk(player_chunk_x, player_chunk_y);
		Load_Chunk(player_chunk_x, player_chunk_y, sprites);
	}

	void Map::Unload_Chunk(int player_chunk_x, int player_chunk_y) {
		int i = 0;
		for (Chunk chunk : loadedchunks) {
			if (chunk.x > player_chunk_x + (CHUNK_AMOUNT_X - 1) / 2 || chunk.x < player_chunk_x - (CHUNK_AMOUNT_X - 1) / 2 || chunk.y > player_chunk_y + (CHUNK_AMOUNT_Y - 1) / 2 || chunk.y < player_chunk_y - (CHUNK_AMOUNT_Y - 1) / 2) {
				std::cout << "unload" << std::endl;
				loadedchunks.erase(loadedchunks.begin() + i);
				i++;
			}
		}
	}

	void Map::Load_Chunk(int player_chunk_x, int player_chunk_y, Sprites* sprites) {
		for (int i = player_chunk_x - (CHUNK_AMOUNT_X - 1) / 2; i <= player_chunk_x + (CHUNK_AMOUNT_X - 1) / 2; i++) {
			for (int j = player_chunk_y - (CHUNK_AMOUNT_Y - 1) / 2; j <= player_chunk_y + (CHUNK_AMOUNT_Y - 1) / 2; j++) {
				Chunk chunk;
				chunk.x = i;
				chunk.y = j;
				std::vector<Chunk> test;
				test.push_back(chunk);
				if (std::search(loadedchunks.begin(), loadedchunks.end(), test.begin(), test.end(), Match) == loadedchunks.end()) {
					std::cout << "load" << std::endl;
					for (int x = 0; x < TILE_AMOUNT_X; x++) {
						for (int y = 0; y < TILE_AMOUNT_Y; y++) {
							Tile tile;
							tile.x = x;
							tile.y = y;
							int dice = rand() % 100;
							if (i > 1000 || j > 6) {
								if (dice % 2 == 0) {
									tile.sprite = sprites->grass;
								}
								else {
									tile.sprite = sprites->rock;
								}
							}
							else {
								tile.sprite = NULL;
							}

							chunk.tiles.push_back(tile);
						}
					}
					loadedchunks.push_back(chunk);
				}
			}
		}
	}



	void Map::Render(Player* player, Sprites* sprites) 
	{

		Check_Chunk(player, sprites);
		for (Chunk chunk : loadedchunks) {
			for (Tile tile : chunk.tiles) {
				SDL_Rect rect_chunk = { tile.x * 16 + chunk.x*TILE_AMOUNT_X*TILE_WIDTH - player->posx*TILE_WIDTH - TILE_WIDTH - WIDTH / 2, tile.y * 16 + chunk.y*TILE_AMOUNT_Y*TILE_HEIGHT - player->posy*TILE_HEIGHT - TILE_HEIGHT - HEIGHT / 2, 16, 16 };
				SDL_Rect rect_chunks = { 0, 0, 16, 16 };
				SDL_RenderCopy(renderer, tile.sprite, &rect_chunks, &rect_chunk);
				
			}
		}


	}

