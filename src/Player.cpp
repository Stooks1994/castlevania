#include "Player.h"

Player::Player(int x, int y, int ts) {
	playerTexture = TextureManager::loadTexture("assets/simon_walking.png");

	red = TextureManager::loadTexture("assets/red.png");
	xDirection = RIGHT;
	yDirection = DOWN;
	state = STOPPED;
	flip = SDL_FLIP_NONE;

	jumping = true;
	jumpKeyDown = false;

	animationTimer = 0.0;

	inputManager = new InputManager();
	stats = new Stats(0, 0, x, y, 250, -1750, -1750, 0.99, Globals::TILESIZE * 2, Globals::TILESIZE);
}

Player::~Player() {

}

void Player::render(SDL_Renderer* rend, Camera* camera) {
	if (animationTimer < 0.5) {
		Globals::SetRect(&srcRect, 0, 0, Globals::TILESIZE / 2, Globals::TILESIZE);
	} else {
		Globals::SetRect(&srcRect, 16, 0, Globals::TILESIZE / 2, Globals::TILESIZE);
	}

	if (state == STOPPED && !jumping) {
		Globals::SetRect(&srcRect, 0, 0, Globals::TILESIZE / 2, Globals::TILESIZE);
	} else if (jumping) {
			Globals::SetRect(&srcRect, 48, 0, Globals::TILESIZE / 2, Globals::TILESIZE);
	} else if (state == MOVING_LEFT || state == MOVING_RIGHT) {
		if (animationTimer < 0.1) {
			Globals::SetRect(&srcRect, 0, 0, Globals::TILESIZE / 2, Globals::TILESIZE);
		} else if (animationTimer < 0.2) {
			Globals::SetRect(&srcRect, 16, 0, Globals::TILESIZE / 2, Globals::TILESIZE);
		} else {
			Globals::SetRect(&srcRect, 32, 0, Globals::TILESIZE / 2, Globals::TILESIZE);
		}
	} else if (state == CROUCHING) {
		Globals::SetRect(&srcRect, 48, 0, Globals::TILESIZE / 2, Globals::TILESIZE);
	}

	//animationManager->getAnimationFrame(state)

	Globals::SetRect(&destRect, (int) stats->getXPos() - camera->xPos, (int) stats->getYPos() - camera->yPos, stats->getWidth(), stats->getHeight());
	SDL_RenderCopyEx(rend, playerTexture, &srcRect, &destRect, 0, NULL, flip);
}

void Player::update(double dt, Camera* camera, int mapWidth, int mapHeight, std::vector<Tile*> _tiles) {
	//animationManager->updateTimer(dt)

	if (state == MOVING_LEFT || state == MOVING_RIGHT) {
		animationTimer += dt;
	}

	if (animationTimer > 0.3) {
		animationTimer = 0;
	}

	updatePlayerPosition(dt, camera, mapWidth, mapHeight, _tiles);
	updateCameraPosition(dt, camera, mapWidth, mapHeight);
}

void Player::updatePlayerPosition(double dt, Camera* camera, int mapWidth, int mapHeight, std::vector<Tile*> _tiles) {
	stats->setYVel(Globals::GRAVITY);

	checkForAndUpdateJump();

	stats->incrementXPos(stats->getXVel() * dt);
	checkCollisionWithTiles(_tiles, X);

	stats->incrementYPos(stats->getYVel() * dt);
	checkCollisionWithTiles(_tiles, Y);

	boundPlayerToCamera(dt, camera);
}

void Player::checkForAndUpdateJump() {
	if (jumpKeyDown)  {
		jump();
	} else {
		if (!jumping) {
			resetJumpForce();
		}
		/*
		if (jumping) {
			stats->setYVel(Globals::GRAVITY);
		} else {
			resetJumpForce();
		}
		*/
	}
}

void Player::updateCameraPosition(double dt, Camera* camera, int mapWidth, int mapHeight) {
	if (stats->getXPos() < (camera->xPos + 0.33 * camera->width) && state == MOVING_LEFT)
		camera->moveCamera(stats->getXVel(), stats->getYVel(), dt, mapWidth, mapHeight);
	else if (stats->getXPos() > (camera->xPos + 0.66 * camera->width) && state == MOVING_RIGHT)
		camera->moveCamera(stats->getXVel(), stats->getYVel(), dt, mapWidth, mapHeight);
	else if (stats->getYPos() < (camera->yPos + 0.33 * camera->height) && yDirection == UP)
		camera->moveCamera(stats->getXVel(), stats->getYVel(), dt, mapWidth, mapHeight);
	else if (stats->getXPos() > (camera->yPos + 0.66 * camera->height) && yDirection == DOWN)
		camera->moveCamera(stats->getXVel(), stats->getYVel(), dt, mapWidth, mapHeight);
}

int Player::handleEvents(SDL_Event event) {
	InputManager* input = InputManager::getInstance();
	std::unordered_set<int> actionsPressed = input->getActionsPressed();

	stats->setXVel(0);

	handleEvents(actionsPressed, KEY_PRESSED);

	return 1;
}

void Player::handleEvents(std::unordered_set<int> actions, int keyEventType) {
	switch (keyEventType) {
	case KEY_DOWN:
		break;
	case KEY_UP:
		break;
	case KEY_PRESSED:
		if (Globals::Contains(actions, Globals::LEFT)) {
			movePlayer(LEFT);
		}

		if (Globals::Contains(actions, Globals::RIGHT)) {
			movePlayer(RIGHT);
		}

		if (Globals::Contains(actions, Globals::DOWN)) {
			state = CROUCHING;
		} else if (state == CROUCHING) {
			state = STOPPED;
		}

		if (Globals::Contains(actions, Globals::JUMP)) {
			if (!jumping) {
				jumpKeyDown = true;
			}
		} else {
			jumpKeyDown = false;
		}

		break;
	}

	if (actions.size() == 0) {
		state = STOPPED;
	}
}

void Player::movePlayer(int direction) {
	switch(direction) {
	case LEFT:
		stats->incrementXVel(stats->getMovespeed() * -1);
		state = MOVING_LEFT;
		flip = SDL_FLIP_NONE;
		break;
	case RIGHT:
		stats->incrementXVel(stats->getMovespeed());
		state = MOVING_RIGHT;
		flip = SDL_FLIP_HORIZONTAL;
		break;
	}
}

void Player::stopPlayer(int direction) {
	switch(direction) {
	case RIGHT: stats->incrementXVel(stats->getMovespeed() * -1); break;
	case LEFT: stats->incrementXVel(stats->getMovespeed()); break;
	}
}

void Player::jump() {
	jumping = true;
	stats->incrementYVel(stats->getJumpForce());
	stats->setJumpForce(stats->getJumpForce() * stats->getJumpDampening());
}

void Player::boundPlayerToCamera(double dt, Camera* camera) {
	double x = stats->getXPos();
	double w = stats->getWidth();
	double y = stats->getYPos();
	double h = stats->getHeight();

	if (x + w > camera->xPos + camera->width)
		stats->setXPos(camera->xPos + camera->width - w);
	if (x < 0)
		stats->setXPos(0);

	if (y + h > camera->yPos + camera->height)
		stats->setYPos(camera->yPos + camera->height - h);
	if (y < 0)
		stats->setYPos(0);
}

void Player::checkCollisionWithTiles(std::vector<Tile*> _tiles, Axis axis) {
	std::vector<Tile*> collidingTiles;

	double x = stats->getXPos();
	double y = stats->getYPos();
	double w = stats->getWidth();
	double h = stats->getHeight();

	for (auto& tile : _tiles) {
		if (tile->hasCollision()) {
			if (Globals::AABB((int) x, (int) y, w, h,
					tile->getXPos(), tile->getYPos(), Globals::TILESIZE, Globals::TILESIZE)) {
				collidingTiles.push_back(tile);
			}
		}
	}

	for (auto& tile : collidingTiles) {
		if (tile->getTexture() != red) {
			tile->setTexture(red);
		}

		if (Globals::AABB((int) stats->getXPos(), (int) stats->getYPos(), stats->getWidth(), stats->getHeight(), tile->getXPos(), tile->getYPos(), Globals::TILESIZE, Globals::TILESIZE)) {
			resolveCollision(tile, axis);
		}
	}
}

void Player::resolveCollision(Tile* tile, Axis axis) {
	switch(axis) {
		case X: {
			double xOverlap = 0;
			double xVel = stats->getXVel();

			if (xVel < 0) {
				xOverlap = tile->getXPos() + Globals::TILESIZE - stats->getXPos();
				stats->incrementXPos(xOverlap);
			} else {
				xOverlap = stats->getXPos() + stats->getWidth() - tile->getXPos();
				stats->incrementXPos(xOverlap * -1);
			}

			break;
		}
		case Y: {
			double yOverlap = 0;
			double yVel = stats->getYVel();

			if (yVel < 0) {
				yOverlap = tile->getYPos() + Globals::TILESIZE - stats->getYPos();
				stats->incrementYPos(yOverlap);
				jumpKeyDown = false; //Bonked head on block
			} else {
				yOverlap = stats->getYPos() + stats->getHeight() - tile->getYPos();
				stats->incrementYPos(yOverlap * -1);
			}

			break;
		}
	}

	jumping = false;
}

int Player::getOverlappingQuadrant(Tile* tile) {
	std::pair<int, int> overlapCenter = calcOverlapCenter(tile);

	if (overlapCenter.first > (tile->getXPos() + Globals::TILESIZE) / 2) {
		if (overlapCenter.second > (tile->getYPos() + Globals::TILESIZE) / 2) {
			return BOTTOM_RIGHT_QUAD;
		} else {
			return BOTTOM_LEFT_QUAD;
		}
	} else {
		if (overlapCenter.second > (tile->getYPos() + Globals::TILESIZE) / 2) {
			return TOP_RIGHT_QUAD;
		} else {
			return TOP_LEFT_QUAD;
		}
	}

}

std::pair<int, int> Player::calcOverlapCenter(Tile* tile) {
	std::pair<int, int> center;
	int xPos, yPos, xOverlap, yOverlap, centerX, centerY = 0;

	if (stats->getXPos() > tile->getXPos()) {
		xOverlap = tile->getXPos() + Globals::TILESIZE - stats->getXPos();
		xPos = tile->getXPos() + Globals::TILESIZE - xOverlap;
	} else {
		xOverlap = stats->getXPos() + stats->getWidth() - tile->getXPos();
		xPos = stats->getXPos() + stats->getWidth() - xOverlap;
	}

	if (stats->getYPos() > tile->getYPos()) {
		yOverlap = tile->getYPos() + Globals::TILESIZE - stats->getYPos();
		yPos = tile->getYPos() + Globals::TILESIZE - yOverlap;
	} else {
		yOverlap = stats->getYPos() + stats->getHeight() - tile->getYPos();
		yPos = stats->getYPos() + stats->getHeight() - yOverlap;
	}

	centerX = (xPos + xOverlap) / 2;
	centerY = (yPos + yOverlap) / 2;
	center.first = centerX;
	center.second = centerY;

	return center;

}
