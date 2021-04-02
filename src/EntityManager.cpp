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

	centerCameraOnPlayer();
	//startCameraOnPlayer(player->getStats());
}

EntityManager::~EntityManager() {

}

void EntityManager::render(SDL_Renderer* rend) {
	map->render(rend, camera);
	player->render(rend, camera);
}

void EntityManager::update(double dt) {
	player->update(dt, camera, mapWidth, mapHeight, map->getTiles());
	centerCameraOnPlayer();
}

int EntityManager::handleEvents(SDL_Event event) {
	return player->handleEvents(event);
}

void EntityManager::centerCameraOnPlayer() {
	Stats* playerStats = player->getStats();
	double playerX = playerStats->getXPos();
	double playerY = playerStats->getYPos();
	int cameraW = camera->width;
	int cameraH = camera->height;

	// Try to center player on camera
	camera->xPos = playerX - (cameraW / 2);
	camera->yPos = playerY - (cameraH / 2);

	if (camera->xPos < 0)
		camera->xPos = 0;
	else if (camera->xPos + cameraW > mapWidth)
		camera->xPos = mapWidth - cameraW;

	if (camera->yPos < 0)
		camera->yPos = 0;
	else if (camera->yPos + cameraH > mapHeight)
		camera->yPos = mapHeight - cameraH;
}

void EntityManager::startCameraOnPlayer(Stats* stats) {
	double playerX = stats->getXPos();
	double playerY = stats->getYPos();
	int cameraW = camera->width;
	int cameraH = camera->height;

	// Try to center player on camera
	camera->xPos = playerX - (cameraW / 2);
	camera->yPos = playerY - (cameraH / 2);

	// Restrict camera to background size
	if (camera->xPos < 0)
		camera->xPos = 0;
	else if (camera->xPos + cameraW > map->getBackgroundW())
		camera->xPos = map->getBackgroundW() - cameraW;

	if (camera->yPos < 0)
		camera->yPos = 0;
	else if (camera->yPos + cameraH > map->getBackgroundH())
		camera->yPos = map->getBackgroundH() - cameraH;
}
