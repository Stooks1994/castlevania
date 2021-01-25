#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "MainMenu.h"
#include <iostream>

class Game {
public:
	Game();
	virtual ~Game();

	void init(const char* title, int windowXPos, int windowYPos, int windowWidth, int windowHeight, bool isFullscreen);
	void update(double dt);
	void render(SDL_Renderer* rend);
	void handleEvents();
	void clean();

	bool getIsRunning() { return isRunning; };

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static MainMenu* mainMenu;

	static int resolutionX;
	static int resolutionY;
	static int currScene;

	static const int tileSize = 32;

	enum Scene { MAIN_MENU, IN_GAME, PAUSE_MENU };

private:
	bool isRunning;
	SDL_Window* window;

};

#endif /* SRC_GAME_H_ */