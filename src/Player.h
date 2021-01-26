#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.h"

class Player {

public:
	Player(int x, int y, int ts);
	virtual ~Player();

	void update(double dt);
	void handleEvents();
	void render(SDL_Renderer* rend);

private:
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Texture* playerTexture;

	double xVel;
	double yVel;
	double xPos;
	double yPos;
	double movespeed;

	int tileSize;
};

#endif /* SRC_PLAYER_H_ */
