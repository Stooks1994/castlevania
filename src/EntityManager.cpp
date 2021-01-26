#include "EntityManager.h"

EntityManager::EntityManager(int ts) {
	tileSize = ts;
	player = new Player(50, 50, ts);
}

EntityManager::~EntityManager() {

}

void EntityManager::render(SDL_Renderer* rend) {
	player->render(rend);
}

void EntityManager::update(double dt) {

}

int EntityManager::handleEvents(SDL_Event event) {
	return 1;
}
