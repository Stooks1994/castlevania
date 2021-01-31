#include "MapData.h"

MapData::MapData() {

}

MapData::MapData(std::vector<Globals::Tile*> _tiles) {
	tiles = _tiles;
}

MapData::~MapData() {
	// TODO Auto-generated destructor stub
}

std::vector<Globals::Tile*> MapData::getTilesOnCamera(Camera* camera) {
	std::vector<Globals::Tile*> tilesOnCamera;

	for (auto& tile : tiles) {
		if (isTileOnCamera(tile, camera)) tilesOnCamera.push_back(tile);
	}

	return tilesOnCamera;
}

bool MapData::isTileOnCamera(Globals::Tile* tile, Camera* camera) {
	if (tile->xPos + Globals::TILESIZE > camera->xPos &&
			tile->xPos < camera->xPos + camera->width &&
			tile->yPos + Globals::TILESIZE > camera->yPos &&
			tile->yPos < camera->yPos + camera->height) {
		return true;
	}

	return false;
}
