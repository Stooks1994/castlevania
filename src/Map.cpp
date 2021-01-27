#include "Map.h"

Map::Map(const char* background) {
	mapTexture = NULL;
	backgroundTexture = TextureManager::loadTexture(background);

	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundW, &backgroundH);
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

void Map::render(SDL_Renderer* rend, Camera* camera) {
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

