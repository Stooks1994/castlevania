#include "Player.h"

Player::Player(int x, int y, int ts) {
	playerTexture = TextureManager::loadTexture("assets/knight_left.png");

	red = TextureManager::loadTexture("assets/red.png");
	currDirection = RIGHT;
	state = STOPPED;

	jumping = true;
	jumpKeyDown = false;

	inputManager = new InputManager();
	stats = new Stats(0, 0, x, y, 350, -1500, -1500, 0.99, Globals::TILESIZE * 2, Globals::TILESIZE);
}

Player::~Player() {

}

void Player::render(SDL_Renderer* rend, Camera* camera) {
	Globals::SetRect(&srcRect, 0, 0, Globals::TILESIZE, Globals::TILESIZE);
	Globals::SetRect(&destRect, (int) stats->getXPos() - camera->xPos, (int) stats->getYPos() - camera->yPos, stats->getWidth(), stats->getHeight());
	SDL_RenderCopy(rend, playerTexture, &srcRect, &destRect);
}

void Player::update(double dt, Camera* camera, int mapWidth, int mapHeight, std::vector<Tile*> _tiles) {
	updatePlayerPosition(dt, camera, mapWidth, mapHeight, _tiles);
	updateCameraPosition(dt, camera, mapWidth, mapHeight);
}

void Player::updatePlayerPosition(double dt, Camera* camera, int mapWidth, int mapHeight, std::vector<Tile*> _tiles) {
	stats->setYVel(Globals::GRAVITY);

	if (jumpKeyDown)  {
		jump();
	} else {
		if (jumping) {
			stats->setYVel(Globals::GRAVITY);
		} else {
			resetJumpForce();
		}
	}

	stats->incrementXPos(stats->getXVel() * dt);
	stats->incrementYPos(stats->getYVel() * dt);

	checkCollisionWithTiles(_tiles);
	boundPlayerToCamera(dt, camera);
}

void Player::updateCameraPosition(double dt, Camera* camera, int mapWidth, int mapHeight) {
	if (stats->getXPos() < (camera->xPos + 0.33 * camera->width) && currDirection == LEFT)
		camera->moveCamera(stats->getXVel(), stats->getYVel(), dt, mapWidth, mapHeight);
	else if (stats->getXPos() > (camera->xPos + 0.66 * camera->width) && currDirection == RIGHT)
		camera->moveCamera(stats->getXVel(), stats->getYVel(), dt, mapWidth, mapHeight);
	else if (stats->getYPos() < (camera->yPos + 0.33 * camera->height) && currDirection == UP)
		camera->moveCamera(stats->getXVel(), stats->getYVel(), dt, mapWidth, mapHeight);
	else if (stats->getXPos() > (camera->yPos + 0.66 * camera->height) && currDirection == DOWN)
		camera->moveCamera(stats->getXVel(), stats->getYVel(), dt, mapWidth, mapHeight);
}

int Player::handleEvents(SDL_Event event) {
	InputManager* input = InputManager::getInstance();
	std::unordered_set<int> actionsDown = input->getActionsDown();
	std::unordered_set<int> actionsUp = input->getActionsUp();

	handleEvents(actionsDown, KEY_DOWN);
	handleEvents(actionsUp, KEY_UP);

	printf("%f\n", stats->getXVel());
	/*
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch(event.key.keysym.sym) {
		case SDLK_a: movePlayer(LEFT); currDirection = LEFT; break;
		case SDLK_d: movePlayer(RIGHT); currDirection = RIGHT; break;
		case SDLK_SPACE: jumpKeyDown = true; break;
		default: break;
		}
	} else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
		switch(event.key.keysym.sym) {
		case SDLK_a: movePlayer(RIGHT); break;
		case SDLK_d: movePlayer(LEFT); break;
		case SDLK_SPACE: jumpKeyDown = false; break;
		default: break;
		}
	}
	*/

	return 1;
}

void Player::handleEvents(std::unordered_set<int> actions, int keyEventType) {
	switch (keyEventType) {
	case KEY_DOWN:
		if (Globals::Contains(actions, Globals::LEFT)) {
			if (state != MOVING_LEFT)
				movePlayer(LEFT);
		}

		else if (Globals::Contains(actions, Globals::RIGHT)) {
			if (state != MOVING_RIGHT)
				movePlayer(RIGHT);
		}

		break;
	case KEY_UP:
		if (Globals::Contains(actions, Globals::LEFT)) {
			if (state == MOVING_LEFT)
				stopPlayer(LEFT);
		}

		else if (Globals::Contains(actions, Globals::RIGHT)) {
			if (state == MOVING_RIGHT)
				stopPlayer(RIGHT);
		}

		break;
	}
}

void Player::movePlayer(int direction) {
	switch(direction) {
	case LEFT:
		stats->incrementXVel(stats->getMovespeed() * -1);
		state = MOVING_LEFT;
		break;
	case RIGHT:
		stats->incrementXVel(stats->getMovespeed());
		state = MOVING_RIGHT;
		break;
	}
}

void Player::stopPlayer(int direction) {
	switch(direction) {
	case RIGHT: stats->incrementXVel(stats->getMovespeed() * -1); break;
	case LEFT: stats->incrementXVel(stats->getMovespeed()); break;
	}

	state = STOPPED;
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

	if (x + w > camera->width)
		stats->setXPos(camera->width - w);
	if (x < 0)
		stats->setXPos(0);

	if (y + h > camera->height)
		stats->setYPos(camera->height - h);
	if (y < 0)
		stats->setYPos(0);
}

void Player::checkCollisionWithTiles(std::vector<Tile*> _tiles) {
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
			resolveCollision(tile);
		}
	}
}

void Player::resolveCollision(Tile* tile) {
	int xOverlap = abs(((int) stats->getXPos()) + stats->getWidth() - tile->getXPos());
	int yOverlap = abs(((int) stats->getYPos()) + stats->getHeight() - tile->getYPos());

	jumping = false;

	if (xOverlap <= yOverlap) {
		stats->incrementXPos(xOverlap * -1);
	} else {
		stats->incrementYPos(yOverlap * -1);
	}
}
