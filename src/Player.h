#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.h"
#include "Camera.h"

class Player {

public:
	Player(int x, int y, int ts);
	virtual ~Player();

	void update(double dt, Camera* camera, int mapWidth, int mapHeight);
	int handleEvents(SDL_Event event);
	void render(SDL_Renderer* rend);

	enum Directions { UP, DOWN, LEFT, RIGHT };

	double GRAVITY;

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

	void movePlayer(int direction);

	void updatePlayerPosition(double dt, Camera* camera, int mapWidth, int mapHeight);
	void updateCameraPosition(double dt, Camera* camera, int mapWidth, int mapHeight);
};

#endif /* SRC_PLAYER_H_ */
