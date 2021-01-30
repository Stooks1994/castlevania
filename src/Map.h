#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.h"
#include "Camera.h"
#include "MapData.h"
#include "Globals.h"

class Map {

public:
	Map(const char* background);
	virtual ~Map();

	int getBackgroundW() { return backgroundW; };
	int getBackgroundH() { return backgroundH; };

	void render(SDL_Renderer* rend, Camera* camera);
	void renderBackground(SDL_Renderer* rend, Camera* camera);
	void renderMap(SDL_Renderer* rend, Camera* camera);

	void update(double dt);

private:
	SDL_Rect srcRect, destRect;
	SDL_Texture* mapTexture;
	SDL_Texture* backgroundTexture;
	MapData* mapData;

	int backgroundW;
	int backgroundH;
};

#endif /* SRC_MAP_H_ */
