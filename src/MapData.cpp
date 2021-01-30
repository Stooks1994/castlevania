#include "MapData.h"

MapData::MapData(int ts) {
	tileSize = ts;

	Tile* tile = new Tile{100, 100, TextureManager::loadTexture("assets/grass_center.png")};
	Tile* tile2 = new Tile{132, 100, TextureManager::loadTexture("assets/grass_end_right.png")};

	tiles.push_back(tile);
	tiles.push_back(tile2);
}

MapData::~MapData() {
	// TODO Auto-generated destructor stub
}

std::vector<MapData::Tile*> MapData::getTilesOnCamera(Camera* camera) {
	std::vector<MapData::Tile*> tilesOnCamera;

	for (auto& tile : tiles) {
		if (isTileOnCamera(tile, camera)) tilesOnCamera.push_back(tile);
	}

	return tilesOnCamera;
}

bool MapData::isTileOnCamera(Tile* tile, Camera* camera) {
	if (tile->xPos + tileSize > camera->xPos &&
			tile->xPos < camera->xPos + camera->width &&
			tile->yPos + tileSize > camera->yPos &&
			tile->yPos < camera->yPos + camera->height) {
		return true;
	}

	return false;
}
