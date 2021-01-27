#include "Player.h"

Player::Player(int x, int y, int ts) {
	tileSize = ts;
	xVel = yVel = 0;
	xPos = x;
	yPos = y;
	movespeed = 200;
	playerTexture = TextureManager::loadTexture("assets/knight_left.png");
}

Player::~Player() {

}

void Player::render(SDL_Renderer* rend) {
	destRect.x = (int) xPos;
	destRect.y = (int) yPos;
	destRect.h = tileSize * 2;
	destRect.w = tileSize;

	srcRect.x = srcRect.y = 0;
	srcRect.h = srcRect.w = tileSize;

	SDL_RenderCopy(rend, playerTexture, &srcRect, &destRect);
}

void Player::update(double dt, Camera* camera, int mapWidth, int mapHeight) {
	updatePlayerPosition(dt, camera, mapWidth, mapHeight);
	updateCameraPosition(dt, camera, mapWidth, mapHeight);
}

void Player::updatePlayerPosition(double dt, Camera* camera, int mapWidth, int mapHeight) {
	xPos += xVel * dt;
	yPos += yVel * dt;

	if (xPos + tileSize > camera->width) xPos = camera->width - tileSize;
	if (xPos < 0) xPos = 0;

	if (yPos + tileSize > camera->height) yPos = camera->height - (2 * tileSize);
	if (yPos < 0) yPos = 0;
}

void Player::updateCameraPosition(double dt, Camera* camera, int mapWidth, int mapHeight) {
	camera->moveCamera(xVel, yVel, dt, mapWidth, mapHeight);
}

int Player::handleEvents(SDL_Event event) {
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch(event.key.keysym.sym) {
		case SDLK_a: movePlayer(LEFT); break;
		case SDLK_d: movePlayer(RIGHT); break;
		default: break;
		}
	} else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
		switch(event.key.keysym.sym) {
		case SDLK_a: movePlayer(RIGHT); break;
		case SDLK_d: movePlayer(LEFT); break;
		default: break;
		}
	}

	return 1;
}

void Player::movePlayer(int direction) {
	switch(direction) {
	case LEFT: xVel -= movespeed; break;
	case RIGHT: xVel += movespeed; break;
	}
}
