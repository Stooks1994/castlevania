#ifndef SRC_MAPDATA_H_
#define SRC_MAPDATA_H_

#include <vector>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Globals.h"

class MapData {

public:
	MapData();
	MapData(std::vector<Globals::Tile*> _tiles);
	virtual ~MapData();

	std::vector<Globals::Tile*> getTilesOnCamera(Camera* camera);

	bool isTileOnCamera(Globals::Tile* tile, Camera* camera);

private:
	std::vector<Globals::Tile*> tiles;

};

#endif /* SRC_MAPDATA_H_ */
