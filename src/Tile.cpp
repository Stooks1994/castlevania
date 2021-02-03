#include "Tile.h"

Tile::Tile(int _xPos, int _yPos, int _xSpriteMap, int _ySpriteMap, bool _hasCollision, SDL_Texture* _tileTexture) {
	xPos = _xPos;
	yPos = _yPos;
	xSpriteMap = _xSpriteMap;
	ySpriteMap = _ySpriteMap;
	collision = _hasCollision;
	tileTexture = _tileTexture;
}

Tile::~Tile() {
	// TODO Auto-generated destructor stub
}

