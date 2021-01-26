#ifndef SRC_ENTITYMANAGER_H_
#define SRC_ENTITYMANAGER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Player.h"

class EntityManager {

public:
	EntityManager(int ts);
	virtual ~EntityManager();

	void render(SDL_Renderer* rend);
	void update(double dt);
	int handleEvents(SDL_Event event);

private:
	Player* player;
	int tileSize;

};

#endif /* SRC_ENTITYMANAGER_H_ */
