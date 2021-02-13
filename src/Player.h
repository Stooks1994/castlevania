#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <vector>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Camera.h"
#include "Globals.h"
#include "Tile.h"
#include "Stats.h"

class Player {

public:
	Player(int x, int y, int ts);
	virtual ~Player();

	void update(double dt, Camera* camera, int mapWidth, int mapHeight, std::vector<Tile*> _tiles);
	int handleEvents(SDL_Event event);
	void render(SDL_Renderer*, Camera*);

	bool isJumping() { return jumping; };

	enum Directions { UP, DOWN, LEFT, RIGHT };

private:
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Texture* playerTexture;
	SDL_Texture* red;
	InputManager* inputManager;
	Stats* stats;

	int currDirection;

	bool jumping;
	bool jumpKeyDown;

	void movePlayer(int direction);
	void jump();
	void jump(double);
	void resetJumpForce() { stats->setJumpForce(stats->getJumpForceMax()); };

	void updatePlayerPosition(double dt, Camera* camera, int mapWidth, int mapHeight, std::vector<Tile*> _tiles);
	void updateCameraPosition(double dt, Camera* camera, int mapWidth, int mapHeight);

	void boundPlayerToCamera(double dt, Camera* camera);
	void checkCollisionWithTiles(std::vector<Tile*>);
	void resolveCollision(Tile*);
};

#endif /* SRC_PLAYER_H_ */
