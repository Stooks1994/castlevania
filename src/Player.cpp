#include "Player.h"

Player::Player(int x, int y, int ts) {
	tileSize = ts;
	xVel = yVel = 0;
	xPos = x;
	yPos = y;
	prevXPos = 0;
	prevYPos = 0;
	movespeed = 200;
	playerTexture = TextureManager::loadTexture("assets/knight_left.png");

	width = Globals::TILESIZE;
	height = Globals::TILESIZE * 2;

	red = TextureManager::loadTexture("assets/red.png");
	currDirection = RIGHT;
}

Player::~Player() {

}

void Player::render(SDL_Renderer* rend, Camera* camera) {
	Globals::SetRect(&srcRect, 0, 0, Globals::TILESIZE, Globals::TILESIZE);
	Globals::SetRect(&destRect, (int) xPos - camera->xPos, (int) yPos - camera->yPos, Globals::TILESIZE, Globals::TILESIZE * 2);

	SDL_RenderCopy(rend, playerTexture, &srcRect, &destRect);
}

void Player::update(double dt, Camera* camera, int mapWidth, int mapHeight, std::vector<Tile*> _tiles) {
	updatePlayerPosition(dt, camera, mapWidth, mapHeight, _tiles);
	updateCameraPosition(dt, camera, mapWidth, mapHeight);
}

void Player::updatePlayerPosition(double dt, Camera* camera, int mapWidth, int mapHeight, std::vector<Tile*> _tiles) {
	prevXPos = xPos;
	prevYPos = yPos;

	xPos += xVel * dt;
	yPos += (yVel * dt) + (Globals::GRAVITY * dt);

	checkCollisionWithTiles(_tiles);
	boundPlayerToCamera(dt, camera);
}

void Player::updateCameraPosition(double dt, Camera* camera, int mapWidth, int mapHeight) {
	if (xPos < (camera->xPos + 0.33 * camera->width) && currDirection == LEFT)
		camera->moveCamera(xVel, yVel, dt, mapWidth, mapHeight);
	if (xPos > (camera->xPos + 0.66 * camera->width) && currDirection == RIGHT)
		camera->moveCamera(xVel, yVel, dt, mapWidth, mapHeight);
}

int Player::handleEvents(SDL_Event event) {
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch(event.key.keysym.sym) {
		case SDLK_a: movePlayer(LEFT); currDirection = LEFT; break;
		case SDLK_d: movePlayer(RIGHT); currDirection = RIGHT; break;
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

void Player::boundPlayerToCamera(double dt, Camera* camera) {
	if (xPos + width > camera->width)
		xPos = camera->width - width;
	if (xPos < 0)
		xPos = 0;

	if (yPos + height > camera->height)
		yPos = camera->height - height;
	if (yPos < 0)
		yPos = 0;
}

void Player::checkCollisionWithTiles(std::vector<Tile*> _tiles) {
	std::vector<Tile*> collidingTiles;

	for (auto& tile : _tiles) {
		if (tile->hasCollision()) {
			if (Globals::AABB((int) xPos, (int) yPos, width, height,
					tile->getXPos(), tile->getYPos(), Globals::TILESIZE, Globals::TILESIZE)) {
				collidingTiles.push_back(tile);
			}
		}
	}

	//printf("%d\n", collidingTiles.size());
	//printf("%f %f\n", this->xPos, this->yPos);

	for (auto& tile : collidingTiles) {
		if (tile->getTexture() != red) {
			tile->setTexture(red);
			printf("Tiles: %d %d      Player: %f %f\n", tile->getXPos(), tile->getYPos(), xPos, yPos);
		}
		if (Globals::AABB((int) xPos, (int) yPos, width, height, tile->getXPos(), tile->getYPos(), Globals::TILESIZE, Globals::TILESIZE)) {
			resolveCollision(tile);
		}
	}
}

void Player::resolveCollision(Tile* tile) {
	int xOverlap = abs(((int) this->xPos) + Globals::TILESIZE - tile->getXPos());
	int yOverlap = abs(((int) this->yPos) + (Globals::TILESIZE * 2) - tile->getYPos());

	if (xOverlap <= yOverlap) {
		this->xPos -= xOverlap;
	} else {
		this->yPos -= yOverlap;
	}
}
