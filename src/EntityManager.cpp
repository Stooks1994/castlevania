#include "EntityManager.h"

EntityManager::EntityManager(int ts, int resX, int resY) {
	tileSize = ts;
	player = new Player(50, 50, ts);
	map = new Map("assets/trees.png");
	camera = new Camera(0.0, 0.0, resX, resY);

	resolutionX = resX;
	resolutionY = resY;

	mapHeight = map->getBackgroundH();
	mapWidth = map->getBackgroundW();
}

EntityManager::~EntityManager() {

}

void EntityManager::render(SDL_Renderer* rend) {
	map->render(rend, camera);
	player->render(rend);
}

void EntityManager::update(double dt) {
	player->update(dt, camera, mapWidth, mapHeight);
}

int EntityManager::handleEvents(SDL_Event event) {
	player->handleEvents(event);
	return 1;
}
