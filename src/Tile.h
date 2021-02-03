#ifndef SRC_TILE_H_
#define SRC_TILE_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Tile {

public:
	Tile(int, int, int, int, bool, SDL_Texture*);
	virtual ~Tile();

	int getXPos() { return xPos; };
	int getYPos() { return yPos; };
	int getXSpriteMap() { return xSpriteMap; };
	int getYSpriteMap() { return ySpriteMap; };
	bool hasCollision() { return collision; };
	SDL_Texture* getTexture() { return tileTexture; };

	void setTexture(SDL_Texture* tex) { tileTexture = tex; };


private:
	int xPos;
	int yPos;
	int xSpriteMap;
	int ySpriteMap;
	bool collision;
	SDL_Texture* tileTexture;
};

#endif /* SRC_TILE_H_ */
