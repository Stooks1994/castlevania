#ifndef SRC_ENTITYMANAGER_H_
#define SRC_ENTITYMANAGER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Player.h"
#include "Map.h"
#include "Camera.h"

class EntityManager {

public:
	EntityManager(int ts, int resX, int resY);
	virtual ~EntityManager();

	void render(SDL_Renderer* rend);
	void update(double dt);
	int handleEvents(SDL_Event event);

private:
	Player* player;
	Map* map;
	Camera* camera;

	int tileSize;
	int resolutionX;
	int resolutionY;
	int mapHeight;
	int mapWidth;

	void startCameraOnPlayer(Stats* stats);
	void centerCameraOnPlayer();

};

#endif /* SRC_ENTITYMANAGER_H_ */
