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
	enum KeyEventType { KEY_UP, KEY_DOWN, KEY_PRESSED };
	enum State { STOPPED, MOVING_LEFT, MOVING_RIGHT, JUMPING };
	enum Quadrant { TOP_LEFT_QUAD, TOP_RIGHT_QUAD, BOTTOM_LEFT_QUAD, BOTTOM_RIGHT_QUAD };
	enum Axis { X, Y };

private:
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_RendererFlip flip;
	SDL_Texture* playerTexture;
	SDL_Texture* red;
	InputManager* inputManager;
	Stats* stats;

	int currDirection;
	int state;

	double animationTimer;

	bool jumping;
	bool jumpKeyDown;

	void movePlayer(int direction);
	void stopPlayer(int direction);
	void jump();
	void jump(double);
	void resetJumpForce() { stats->setJumpForce(stats->getJumpForceMax()); };

	void updatePlayerPosition(double dt, Camera* camera, int mapWidth, int mapHeight, std::vector<Tile*> _tiles);
	void updateCameraPosition(double dt, Camera* camera, int mapWidth, int mapHeight);

	void boundPlayerToCamera(double dt, Camera* camera);
	void checkCollisionWithTiles(std::vector<Tile*>, Axis axis);
	void resolveCollision(Tile* tile, Axis axis);

	void handleEvents(std::unordered_set<int> actions, int keyEventType);

	int getOverlappingQuadrant(Tile* tile);
	std::pair<int, int> calcOverlapCenter(Tile* tile);
};

#endif /* SRC_PLAYER_H_ */
