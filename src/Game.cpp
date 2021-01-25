#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

MainMenu* Game::mainMenu;

int Game::resolutionX = 800;
int Game::resolutionY = 640;
int Game::currScene = MAIN_MENU;

Game::Game() {
	isRunning = true;
	window = NULL;
}

Game::~Game() {

}

void Game::init(const char* title, int windowXPos, int windowYPos, int windowWidth, int windowHeight, bool isFullscreen) {
	int flags = 0;

	if (isFullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, windowXPos, windowYPos, windowWidth, windowHeight, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;
	} else {
		isRunning = false;
	}

	Game::mainMenu = new MainMenu(Game::resolutionX, Game::resolutionY);
}

void Game::update(double dt) {

}

void Game::render(SDL_Renderer* rend) {
	SDL_RenderClear(rend);

	switch(Game::currScene) {
	case MAIN_MENU:
		Game::mainMenu->render(rend);
		break;
	case IN_GAME:
		break;
	case PAUSE_MENU:
		break;
	default:
		break;
	}

	SDL_RenderPresent(rend);
}

void Game::handleEvents() {
	while(SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT)
			isRunning = false;

		switch(Game::currScene) {
		case MAIN_MENU:
			mainMenu->handleEvents(Game::event);
			break;
		case IN_GAME:
			break;
		case PAUSE_MENU:
			break;
		default:
			break;
		}
		//player->handleEvents();
	}
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
