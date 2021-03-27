#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

MainMenu* Game::mainMenu;
EntityManager* Game::entityManager;

int Game::resolutionX = 800;
int Game::resolutionY = 640;
int Game::logicalResX = 800;
int Game::logicalResY = 640;
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
		SDL_RenderSetLogicalSize(renderer, Game::logicalResX, Game::logicalResY);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;
	} else {
		isRunning = false;
	}

	//Game::mainMenu = new MainMenu(Game::resolutionX, Game::resolutionY);
	//Game::entityManager = new EntityManager(tileSize, Game::resolutionX, Game::resolutionY);
	Game::mainMenu = new MainMenu(Game::logicalResX, Game::logicalResY);
	Game::entityManager = new EntityManager(tileSize, Game::logicalResX, Game::logicalResY);
}

void Game::update(double dt) {
	InputManager* input = InputManager::getInstance();
	input->update(Game::event);

	switch(Game::currScene) {
	case MAIN_MENU:
		break;
	case IN_GAME:
		Game::entityManager->update(dt);
		break;
	case PAUSE_MENU:
		break;
	default:
		break;
	}
}

void Game::render(SDL_Renderer* rend) {
	SDL_RenderClear(rend);

	switch(Game::currScene) {
	case MAIN_MENU:
		Game::mainMenu->render(rend);
		break;
	case IN_GAME:
		Game::entityManager->render(rend);
		break;
	case PAUSE_MENU:
		break;
	default:
		break;
	}

	SDL_RenderPresent(rend);
}

void Game::handleEvents() {
	switch(Game::currScene) {
	case MAIN_MENU:
		updateScene(mainMenu->handleEvents(Game::event));
		break;
	case IN_GAME:
		updateScene(entityManager->handleEvents(Game::event));
		break;
	case PAUSE_MENU:
		break;
	default:
		break;
	}
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::updateScene(int menuSelection) {
	switch (menuSelection) {
	case MainMenu::MAIN_MENU:
		Game::currScene = MAIN_MENU;
		break;
	case MainMenu::GAME_START:
		Game::currScene = IN_GAME;
		break;
	case MainMenu::OPTIONS:
		Game::currScene = OPTIONS;
		break;
	case MainMenu::EXIT:
		isRunning = false;
		break;
	default:
		break;
	}
}
