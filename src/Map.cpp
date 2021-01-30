#include "Map.h"

Map::Map(const char* background) {
	mapTexture = NULL;
	mapData = new MapData();
	backgroundTexture = TextureManager::loadTexture(background);

	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundW, &backgroundH);
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

void Map::render(SDL_Renderer* rend, Camera* camera) {
	renderBackground(rend, camera);
	renderMap(rend, camera);
}

void Map::renderMap(SDL_Renderer* rend, Camera* camera) {
	std::vector<MapData::Tile*> tilesOnCamera = mapData->getTilesOnCamera(camera);

	for (auto& tile : tilesOnCamera) {
		Globals::set_rect(&srcRect, 0, 0, Globals::TILESIZE, Globals::TILESIZE);
		Globals::set_rect(&destRect, tile->xPos - camera->xPos, tile->yPos - camera->yPos, Globals::TILESIZE, Globals::TILESIZE);

		SDL_RenderCopy(rend, tile->tileTexture, &srcRect, &destRect);
	}
}

void Map::renderBackground(SDL_Renderer* rend, Camera* camera) {
	Globals::set_rect(&srcRect, camera->xPos, camera->yPos, camera->width, camera->height);
	Globals::set_rect(&destRect, 0, 0, camera->width, camera->height);

	SDL_RenderCopy(rend, backgroundTexture, &srcRect, &destRect);
}

