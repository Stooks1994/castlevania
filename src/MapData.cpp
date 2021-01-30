#include "MapData.h"

MapData::MapData() {
	Globals::Tile* tile = new Globals::Tile{100, 100, TextureManager::loadTexture("assets/grass_center.png")};
	Globals::Tile* tile2 = new Globals::Tile{132, 100, TextureManager::loadTexture("assets/grass_end_right.png")};
	Globals::Tile* tile3 = new Globals::Tile { -10, 100, TextureManager::loadTexture("assets/grass_center.png")};

	tiles.push_back(tile);
	tiles.push_back(tile2);
	tiles.push_back(tile3);
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
