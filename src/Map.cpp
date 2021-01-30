#include "Map.h"

Map::Map(const char* background, int ts) {
	mapTexture = NULL;
	mapData = new MapData(ts);
	backgroundTexture = TextureManager::loadTexture(background);

	tileSize = ts;

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
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.h = tileSize;
		srcRect.w = tileSize;

		destRect.x = tile->xPos - camera->xPos;
		destRect.y = tile->yPos - camera->yPos;
		destRect.h = tileSize;
		destRect.w = tileSize;

		printf("%d %d\n", destRect.x, destRect.y);
		SDL_RenderCopy(rend, tile->tileTexture, &srcRect, &destRect);
	}
}

void Map::renderBackground(SDL_Renderer* rend, Camera* camera) {
	srcRect.x = camera->xPos;
	srcRect.y = camera->yPos;
	srcRect.w = camera->width;
	srcRect.h = camera->height;

	destRect.x = 0;
	destRect.y = 0;
	destRect.w = camera->width;
	destRect.h = camera->height;

	SDL_RenderCopy(rend, backgroundTexture, &srcRect, &destRect);
}

