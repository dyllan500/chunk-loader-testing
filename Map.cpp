#include "Map.h"
#include "Game.h"

	Map::Map(SDL_Renderer* ren)
	{
		renderer = ren;
		std::vector<Chunk> loadedchunks;
		std::vector<Chunks> chunks;
		int light_x;
		int light_y;
		reload = false;
    Init();
	}


	void Map::MouseLight(int mouse_x, int mouse_y){
    light_x = mouse_x;
    light_y = mouse_y;
	}



	bool Map::Match(Chunk m1, Chunk m2) {
		return m1.x == m2.x && m1.y == m2.y;
	}

	void Map::Init(){
	  FILE *fptr;
    fptr = fopen("map1.dat","rb");
    fread(&chunks, sizeof(chunks), 1, fptr);
    fclose(fptr);
	}

	bool Map::Check_Collision(char dir, int player_x, int player_y, Tiles* tiles){
	  int posX = 0;
    int posY = 0;
    SDL_Rect temp_rect;
    SDL_Rect rect_chunk;
    bool result = false;
    for (Chunk chunk : loadedchunks) {
        for (Tile tile : chunk.tiles){
          posX = chunk.x*TILE_AMOUNT_X*TILE_WIDTH*PIXEL_SIZE - player_x*TILE_WIDTH*PIXEL_SIZE - TILE_WIDTH*PIXEL_SIZE/2 + WIDTH/2;
          posY = chunk.y*TILE_AMOUNT_Y*TILE_WIDTH*PIXEL_SIZE - player_y*TILE_WIDTH*PIXEL_SIZE - TILE_WIDTH*PIXEL_SIZE/2 + HEIGHT/2;
          if (dir == 'n'){
            rect_chunk = {tile.x*TILE_WIDTH*PIXEL_SIZE + posX, tile.y*TILE_WIDTH*PIXEL_SIZE + posY + TILE_HEIGHT, TILE_WIDTH*PIXEL_SIZE, TILE_WIDTH*PIXEL_SIZE};
          }else if (dir == 's'){
            rect_chunk = {tile.x*TILE_WIDTH*PIXEL_SIZE + posX, tile.y*TILE_WIDTH*PIXEL_SIZE + posY - TILE_HEIGHT, TILE_WIDTH*PIXEL_SIZE, TILE_WIDTH*PIXEL_SIZE};
          }else if (dir == 'w'){
            rect_chunk = {tile.x*TILE_WIDTH*PIXEL_SIZE + posX + TILE_HEIGHT, tile.y*TILE_WIDTH*PIXEL_SIZE + posY, TILE_WIDTH*PIXEL_SIZE, TILE_WIDTH*PIXEL_SIZE};
          }else{
            rect_chunk = {tile.x*TILE_WIDTH*PIXEL_SIZE + posX - TILE_HEIGHT, tile.y*TILE_WIDTH*PIXEL_SIZE + posY, TILE_WIDTH*PIXEL_SIZE, TILE_WIDTH*PIXEL_SIZE};
          }
          SDL_Rect player_rect = { (WIDTH / 2), (HEIGHT / 2), PLAYER_WIDTH * PIXEL_SIZE, PLAYER_HEIGHT *PIXEL_SIZE};
          if (!result){
            result = SDL_IntersectRect(&rect_chunk, &player_rect, &temp_rect);
            if (!tile.collision){
              result = false;
            }
          }
        }
		}
		return result;
	}

	void Map::RemoveTile(int mouse_x, int mouse_y, int player_x, int player_y, Tiles* tiles, Player* player){
    int posX = 0;
    int posY = 0;
    int tile_loc = 0;
    int chunk_x = -1;
    int chunk_y = -1;
    for (Chunk chunk : loadedchunks) {
        int i = -1;
        for (Tile tile : chunk.tiles){
          posX = chunk.x*TILE_AMOUNT_X*TILE_WIDTH*PIXEL_SIZE - player_x*TILE_WIDTH*PIXEL_SIZE - TILE_WIDTH*PIXEL_SIZE/2 + WIDTH/2;
          posY = chunk.y*TILE_AMOUNT_Y*TILE_WIDTH*PIXEL_SIZE - player_y*TILE_WIDTH*PIXEL_SIZE - TILE_WIDTH*PIXEL_SIZE/2 + HEIGHT/2;
          if (mouse_x > tile.x*TILE_WIDTH*PIXEL_SIZE + posX && mouse_x < tile.x*TILE_WIDTH*PIXEL_SIZE + posX + TILE_WIDTH && mouse_y > tile.y*TILE_WIDTH*PIXEL_SIZE + posY && mouse_y < tile.y*TILE_WIDTH*PIXEL_SIZE + posY + TILE_HEIGHT){
            tile_loc = i+1;
            chunk_x = chunk.x;
            chunk_y = chunk.y;
          }
          i++;
      }
		}
    for (int x = 0; x < (CHUNK_SIZE_X*CHUNK_SIZE_Y); x++){
      if (chunk_x == int(chunks[x].x) && chunk_y == int(chunks[x].y)){
        for (int y = 0; y < chunks[x].tile_ids.size(); y++){
          if (y == tile_loc){
            if (chunks[x].tile_ids[y].type != NONE){
              if (chunks[x].tile_ids[y].type == Tree_Top){
                  if (chunks[x].tile_ids[y].x == Uint16(1) && chunks[x].tile_ids[y].y == Uint16(2)){
                    handle_tree_tops(x, y, Tree_Top, true, player);
                  }
              }else{
                player->AddItemtoInventory(chunks[x].tile_ids[y].type);
                chunks[x].tile_ids[y].type = NONE;
              }
            }
            reload = true;
          }
        }
      }
    }
	}

	void Map::AddTile(int mouse_x, int mouse_y, int player_x, int player_y, Tiles* tiles, Player* player){
    int posX = 0;
    int posY = 0;
    int tile_loc = 0;
    int chunk_x = -1;
    int chunk_y = -1;
    for (Chunk chunk : loadedchunks) {
        int i = -1;
        for (Tile tile : chunk.tiles){
          posX = chunk.x*TILE_AMOUNT_X*TILE_WIDTH*PIXEL_SIZE - player_x*TILE_WIDTH*PIXEL_SIZE - TILE_WIDTH*PIXEL_SIZE/2 + WIDTH/2;
          posY = chunk.y*TILE_AMOUNT_Y*TILE_WIDTH*PIXEL_SIZE - player_y*TILE_WIDTH*PIXEL_SIZE - TILE_WIDTH*PIXEL_SIZE/2 + HEIGHT/2;
          if (mouse_x > tile.x*TILE_WIDTH*PIXEL_SIZE + posX && mouse_x < tile.x*TILE_WIDTH*PIXEL_SIZE + posX + TILE_WIDTH && mouse_y > tile.y*TILE_WIDTH*PIXEL_SIZE + posY && mouse_y < tile.y*TILE_WIDTH*PIXEL_SIZE + posY + TILE_HEIGHT){
            tile_loc = i+1;
            chunk_x = chunk.x;
            chunk_y = chunk.y;
          }
          i++;
      }
		}
    for (int x = 0; x < (CHUNK_SIZE_X*CHUNK_SIZE_Y); x++){
      if (chunk_x == int(chunks[x].x) && chunk_y == int(chunks[x].y)){
        for (int y = 0; y < chunks[x].tile_ids.size(); y++){
          if (y == tile_loc){
            if (chunks[x].tile_ids[y].type == NONE){
              if (player->intventory.size() > 0 && player->intventory[player->selected].amount > 0){
                player->RemoveItemtoInventory(player->intventory[player->selected].id);
                if (player->intventory[player->selected].id != Tree_Top){
                  chunks[x].tile_ids[y].type = Uint16(player->intventory[player->selected].id);
                  chunks[x].tile_ids[y].x = Uint16(0);
                  chunks[x].tile_ids[y].y = Uint16(0);
                }else{
                  handle_tree_tops(x, y, player->intventory[player->selected].id, false, player);
                }
              }
            }
            reload = true;
          }
        }
      }
    }
	}

  void Map::handle_tree_tops(int i, int j, Uint16 id, bool remove_tree, Player* player){
    if (remove_tree){
      player->AddItemtoInventory(chunks[i].tile_ids[j].type);
      chunks[i].tile_ids[j+10-1].type = NONE;
      chunks[i].tile_ids[j-1].type = NONE;
      chunks[i].tile_ids[j-10-1].type = NONE;
      chunks[i].tile_ids[j+10-2].type = NONE;
      chunks[i].tile_ids[j-2].type = NONE;
      chunks[i].tile_ids[j-10-2].type = NONE;
      chunks[i].tile_ids[j+10].type = NONE;
      chunks[i].tile_ids[j-10].type = NONE;
      chunks[i].tile_ids[j].type = NONE;
    }else{
      chunks[i].tile_ids[j].type = id;
      chunks[i].tile_ids[j].x = Uint16(1);
      chunks[i].tile_ids[j].y = Uint16(2);
      chunks[i].tile_ids[j+10-1].type = id;
      chunks[i].tile_ids[j+10-1].x = Uint16(2);
      chunks[i].tile_ids[j+10-1].y = Uint16(1);
      chunks[i].tile_ids[j-1].type = id;
      chunks[i].tile_ids[j-1].x = Uint16(1);
      chunks[i].tile_ids[j-1].y = Uint16(1);
      chunks[i].tile_ids[j-10-1].type = id;
      chunks[i].tile_ids[j-10-1].x = Uint16(0);
      chunks[i].tile_ids[j-10-1].y = Uint16(1);
      chunks[i].tile_ids[j+10-2].type = id;
      chunks[i].tile_ids[j+10-2].x = Uint16(2);
      chunks[i].tile_ids[j+10-2].y = Uint16(0);
      chunks[i].tile_ids[j-2].type = id;
      chunks[i].tile_ids[j-2].x = Uint16(1);
      chunks[i].tile_ids[j-2].y = Uint16(0);
      chunks[i].tile_ids[j-10-2].type = id;
      chunks[i].tile_ids[j-10-2].x = Uint16(0);
      chunks[i].tile_ids[j-10-2].y = Uint16(0);
      chunks[i].tile_ids[j+10].type = id;
      chunks[i].tile_ids[j+10].x = Uint16(2);
      chunks[i].tile_ids[j+10].y = Uint16(2);
      chunks[i].tile_ids[j-10].type = id;
      chunks[i].tile_ids[j-10].x = Uint16(0);
      chunks[i].tile_ids[j-10].y = Uint16(2);
    }
  }

	void Map::Check_Chunk(Player* player, Tiles* tiles) {
		int player_chunk_x = player->posx / TILE_AMOUNT_X;
		int player_chunk_y = player->posy / TILE_AMOUNT_Y;
		bool haveToLoad = Unload_Chunk(player_chunk_x, player_chunk_y, tiles);
		if (haveToLoad || reload){
      Load_Chunk(player_chunk_x, player_chunk_y, tiles);
		}
	}

	bool Map::Unload_Chunk(int player_chunk_x, int player_chunk_y, Tiles* tiles) {
		int i = 0;
		bool unloaded_Chunk = false;
		for (Chunk chunk : loadedchunks) {
			if (chunk.x > player_chunk_x + (CHUNK_AMOUNT_X - 1) / 2 || chunk.x < player_chunk_x - (CHUNK_AMOUNT_X - 1) / 2 || chunk.y > player_chunk_y + (CHUNK_AMOUNT_Y - 1) / 2 || chunk.y < player_chunk_y - (CHUNK_AMOUNT_Y - 1) / 2) {
				loadedchunks.erase(loadedchunks.begin() + i);
				i++;
				unloaded_Chunk = true;
			}
		}
		if (loadedchunks.size() == 0){
      unloaded_Chunk = true;
		}
		if (reload){
      loadedchunks.erase(loadedchunks.begin(), loadedchunks.end());
		}
		return unloaded_Chunk;
	}

	void Map::Load_Chunk(int player_chunk_x, int player_chunk_y, Tiles* tiles) {
		for (int i = player_chunk_x - (CHUNK_AMOUNT_X - 1) / 2; i <= player_chunk_x + (CHUNK_AMOUNT_X - 1) / 2; i++) {
			for (int j = player_chunk_y - (CHUNK_AMOUNT_Y - 1) / 2; j <= player_chunk_y + (CHUNK_AMOUNT_Y - 1) / 2; j++) {
				Chunk chunk;
				chunk.x = i;
				chunk.y = j;
        int tile_loc = -1;
				for (int x = 0; x < (CHUNK_SIZE_X*CHUNK_SIZE_Y); x++){
            if (i == int(chunks[x].x) && j == int(chunks[x].y)){
              tile_loc = x;
          }
        }
				std::vector<Chunk> test;
				test.push_back(chunk);
				if (std::search(loadedchunks.begin(), loadedchunks.end(), test.begin(), test.end(), Match) == loadedchunks.end()) {
					for (int x = 0; x < TILE_AMOUNT_X; x++) {
						for (int y = 0; y < TILE_AMOUNT_Y; y++) {
							Tile tile;
							tile.x = x;
							tile.y = y;
							if(tile_loc != -1){
                if (chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].type == Grass) {
									tile.sprite = tiles->grass;
									tile.sprite_x = chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].x;
									tile.sprite_y = chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].y;
									tile.collision = true;
								}else if (chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].type == Stone) {
									tile.sprite = tiles->stone;
									tile.sprite_x = chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].x;
									tile.sprite_y = chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].y;
									tile.collision = true;
								}else if (chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].type == Tree) {
									tile.sprite = tiles->tree_o;
									tile.sprite_x = chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].x;
									tile.sprite_y = chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].y;
									tile.collision = false;
								}else if (chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].type == Tree_Top) {
									tile.sprite = tiles->tree_top;
									tile.sprite_x = chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].x;
									tile.sprite_y = chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].y;
									tile.collision = false;
								}else if (chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].type == Dirt) {
									tile.sprite = tiles->dirt;
									tile.sprite_x = chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].x;
									tile.sprite_y = chunks[tile_loc].tile_ids[(TILE_AMOUNT_X*x)+y].y;
									tile.collision = true;
								}
								else{
                  tile.sprite = NULL;
                  tile.collision = false;
								}
							}else{
                tile.sprite = NULL;
                tile.collision = false;
							}
							chunk.tiles.push_back(tile);
						}
					}
					loadedchunks.push_back(chunk);
				}
			}
		}
	}

	void Map::Render(Player* player, Tiles* tiles)
	{
    Check_Chunk(player, tiles);
    int posX = 0;
    int posY = 0;
    bool result;
    bool results;
    bool resultss;
    SDL_Rect temp_rect;
		for (Chunk chunk : loadedchunks) {
			for (Tile tile : chunk.tiles) {
        posX = chunk.x*TILE_AMOUNT_X*TILE_WIDTH*PIXEL_SIZE - player->posx*TILE_WIDTH*PIXEL_SIZE - TILE_WIDTH*PIXEL_SIZE/2 + WIDTH/2;
        posY = chunk.y*TILE_AMOUNT_Y*TILE_WIDTH*PIXEL_SIZE - player->posy*TILE_WIDTH*PIXEL_SIZE - TILE_WIDTH*PIXEL_SIZE/2 + HEIGHT/2;
				SDL_Rect rect_chunk = {tile.x*TILE_WIDTH*PIXEL_SIZE + posX, tile.y*TILE_WIDTH*PIXEL_SIZE + posY, TILE_WIDTH*PIXEL_SIZE, TILE_WIDTH*PIXEL_SIZE};
				SDL_Rect rect_chunks = { 0, 0, TILE_WIDTH, TILE_HEIGHT };
				SDL_Rect rect_light = {light_x-64, light_y-64, 128, 128};
				SDL_Rect rect_lights = {light_x-128, light_y-128, 232, 232};
				SDL_Rect rect_lightss = {light_x-16, light_y-16, 32, 32};
				//SDL_SetTextureAlphaMod(tile.sprite, Uint8(1));
				//SDL_BlendMode blend = SDL_BLENDMODE_BLEND;
				//SDL_SetTextureBlendMode(tile.sprite, blend);
				/*result = SDL_IntersectRect(&rect_chunk, &rect_light, &temp_rect);
				results = SDL_IntersectRect(&rect_chunk, &rect_lights, &temp_rect);
				resultss = SDL_IntersectRect(&rect_chunk, &rect_lightss, &temp_rect);
				if (results){
          SDL_SetTextureAlphaMod(tile.sprite, Uint8(75));
				}
				if (result){
          SDL_SetTextureAlphaMod(tile.sprite, Uint8(150));
				}
				if (resultss){
          SDL_SetTextureAlphaMod(tile.sprite, Uint8(255));
				}*/
				if (tile.sprite != NULL){
          //SDL_RenderCopy(renderer, tiles->fade, &rect_chunks, &rect_chunk);
				}
				SDL_SetTextureColorMod(tile.sprite, Uint8(255), Uint8(255), Uint8(255));
				if (tile.sprite == tiles->tree_top){
            SDL_Rect rect_chunke = {tile.x*TILE_WIDTH*PIXEL_SIZE + posX, tile.y*TILE_WIDTH*PIXEL_SIZE + posY, TILE_WIDTH*PIXEL_SIZE, TILE_WIDTH*PIXEL_SIZE};
            SDL_Rect rect_chunkse = { tile.sprite_x*TILE_WIDTH, tile.sprite_y*TILE_WIDTH, TILE_WIDTH, TILE_HEIGHT };
            SDL_RenderCopy(renderer, tile.sprite, &rect_chunkse, &rect_chunke);
          }else{
            SDL_RenderCopy(renderer, tile.sprite, &rect_chunks, &rect_chunk);
          }

			}
		}
		for (Chunk chunk : loadedchunks) {
			for (Tile tile : chunk.tiles) {
        tile.sprite = tiles->grass;

			}
		}
	}


