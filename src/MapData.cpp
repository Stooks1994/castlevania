#include "MapData.h"

MapData::MapData() {

}

MapData::MapData(std::vector<Tile*> _tiles) {
	tiles = _tiles;
}

MapData::~MapData() {
	// TODO Auto-generated destructor stub
}

std::vector<Tile*> MapData::getTilesOnCamera(Camera* camera) {
	std::vector<Tile*> tilesOnCamera;

	for (auto& tile : tiles) {
		if (isTileOnCamera(tile, camera)) tilesOnCamera.push_back(tile);
	}

	return tilesOnCamera;
}

bool MapData::isTileOnCamera(Tile* tile, Camera* camera) {
	if (tile->getXPos() + Globals::TILESIZE > camera->xPos &&
			tile->getXPos() < camera->xPos + camera->width &&
			tile->getYPos() + Globals::TILESIZE > camera->yPos &&
			tile->getYPos() < camera->yPos + camera->height) {
		return true;
	}

	return false;
}

void MapData::printTile(int _x, int _y) {
	for (auto& tile : tiles) {
		if (tile->getXPos() == _x * Globals::TILESIZE && tile->getYPos() == _y * Globals::TILESIZE) {
			printf("%d %d ", tile->getXPos(), tile->getXPos());
			if (tile->hasCollision()) {
				printf("True\n");
			} else {
				printf("False\n");
			}
		}
	}
}
