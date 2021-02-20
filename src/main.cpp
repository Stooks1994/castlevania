#include <iostream>
#include "Game.h"
#include "InputManager.h"

Game* game = nullptr;

int main(int argc, const char* argv[]) {
	game = new Game();
	game->init("CastleVania", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::resolutionX, Game::resolutionY, false);

	Uint32 minimum_t = 1000 / 6;
	Uint32 dt = 0;
	Uint32 last_t = 0;
	Uint32 curr_t = 0;

	while (InputManager::getInstance()->isRunning()) {
		curr_t = SDL_GetTicks();

		if (last_t < curr_t) {
			dt = curr_t - last_t;

			if (dt > minimum_t)
				dt = minimum_t;

			game->handleEvents();
			game->update(dt / 1000.f);
			game->render(Game::renderer);

			last_t = curr_t;
		} else {
			SDL_Delay(1);
		}
	}

	game->clean();
	return 0;
}

