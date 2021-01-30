#ifndef SRC_MAPDATA_H_
#define SRC_MAPDATA_H_

#include <vector>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.h"
#include "Camera.h"

class MapData {

public:
	MapData(int ts);
	virtual ~MapData();

	struct Tile {
		int xPos;
		int yPos;
		SDL_Texture* tileTexture;
	};

	std::vector<Tile*> getTilesOnCamera(Camera* camera);

	bool isTileOnCamera(Tile* tile, Camera* camera);

private:
	std::vector<Tile*> tiles;
	int tileSize;

};

#endif /* SRC_MAPDATA_H_ */
