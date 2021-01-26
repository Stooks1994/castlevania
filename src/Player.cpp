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
	destRect.h = destRect.w = tileSize;

	srcRect.x = srcRect.y = 0;
	srcRect.h = srcRect.w = tileSize;

	SDL_RenderCopy(rend, playerTexture, &srcRect, &destRect);
}

