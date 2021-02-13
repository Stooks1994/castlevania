#include "Map.h"

Map::Map(const char* background) {
	level = new LevelLoader("levels/testLevel.txt");
	backgroundTexture = level->getBackgroundTexture();
	mapTexture = NULL;
	mapData = new MapData(level->getTiles());

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
	std::vector<Tile*> tilesOnCamera = mapData->getTilesOnCamera(camera);

	for (auto& tile : tilesOnCamera) {
		Globals::SetRect(&srcRect, tile->getXSpriteMap(), tile->getYSpriteMap(), Globals::TILESIZE, Globals::TILESIZE);
		Globals::SetRect(&destRect, tile->getXPos() - camera->xPos, tile->getYPos() - camera->yPos, Globals::TILESIZE, Globals::TILESIZE);

		SDL_RenderCopy(rend, tile->getTexture(), &srcRect, &destRect);
	}
}

void Map::renderBackground(SDL_Renderer* rend, Camera* camera) {
	Globals::SetRect(&srcRect, camera->xPos, camera->yPos, camera->width, camera->height);
	Globals::SetRect(&destRect, 0, 0, camera->width, camera->height);

	SDL_RenderCopy(rend, backgroundTexture, &srcRect, &destRect);
}

