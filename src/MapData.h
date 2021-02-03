#ifndef SRC_MAPDATA_H_
#define SRC_MAPDATA_H_

#include <vector>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Globals.h"
#include "Tile.h"

class MapData {

public:
	MapData();
	MapData(std::vector<Tile*> _tiles);
	virtual ~MapData();

	std::vector<Tile*> getTilesOnCamera(Camera* camera);
	std::vector<Tile*> getTiles() { return tiles; };

	bool isTileOnCamera(Tile* tile, Camera* camera);

	void printTile(int, int);

private:
	std::vector<Tile*> tiles;

};

#endif /* SRC_MAPDATA_H_ */
