#include "EntityManager.h"

EntityManager::EntityManager(int ts, int resX, int resY) {
	tileSize = ts;
	map = new Map("assets/trees.png");

	std::pair<int, int> playerSpawn = map->getPlayerSpawn();

	player = new Player(playerSpawn.first, playerSpawn.second, ts);
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
	player->render(rend, camera);
}

void EntityManager::update(double dt) {
	player->update(dt, camera, mapWidth, mapHeight, map->getTiles());
}

int EntityManager::handleEvents(SDL_Event event) {
	return player->handleEvents(event);
	//return 1;
}
