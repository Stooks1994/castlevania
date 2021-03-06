#include "MainMenu.h"

MainMenu::MainMenu(int resX, int resY) {
	resolutionX = resX;
	resolutionY = resY;
	screenCenterX = resX / 2;
	screenCenterY = resY / 2;
	currSelection = GAME_START;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 0;
	srcRect.h = 0;

	destRect.x = 0;
	destRect.y = 0;
	destRect.w = 0;
	destRect.h = 0;

	backgroundTexture = TextureManager::loadTexture("assets/mainmenu_background.png");
	selectionsTexture = TextureManager::loadTexture("assets/mainmenu_selections.png");
}

MainMenu::~MainMenu() {

}

void MainMenu::render(SDL_Renderer* rend){
	renderBackground(rend);
	renderSelections(rend);
}

int MainMenu::handleEvents(SDL_Event event) {
	InputManager* input = InputManager::getInstance();
	std::unordered_set<int> actions = input->getActionsDown();

	int menuSelectionValue = MAIN_MENU;

	if (Globals::Contains(actions, Globals::UP)) {
		currSelection--;
		currSelection = boundCurrSelection();
	}
	else if (Globals::Contains(actions, Globals::DOWN)) {
		currSelection++;
		currSelection = boundCurrSelection();
	}
	else if (Globals::Contains(actions, Globals::SELECT)) {
		menuSelectionValue = currSelection;
	}

	return menuSelectionValue;
}

void MainMenu::renderBackground(SDL_Renderer* rend) {
	srcRect.w = destRect.w = resolutionX;
	srcRect.h = destRect.h = resolutionY;

	srcRect.x = srcRect.y = 0;
	destRect.x = destRect.y = 0;

	SDL_RenderCopy(rend, backgroundTexture, &srcRect, &destRect);
}

void MainMenu::renderSelections(SDL_Renderer* rend) {
	renderGameStart(rend);
	renderOptions(rend);
	renderExit(rend);
}

void MainMenu::renderGameStart(SDL_Renderer* rend) {
	srcRect.w = destRect.w = 200;
	srcRect.h = destRect.h = 50;

	srcRect.x = 0;
	if (currSelection == GAME_START) {
		srcRect.y = 50;
	} else {
		srcRect.y = 0;
	}

	destRect.x = screenCenterX - 100;
	destRect.y = screenCenterY - 25;

	SDL_RenderCopy(rend, selectionsTexture, &srcRect, &destRect);
}

void MainMenu::renderOptions(SDL_Renderer* rend) {
	srcRect.w = destRect.w = 200;
	srcRect.h = destRect.h = 50;

	srcRect.x = 0;
	if (currSelection == OPTIONS) {
		srcRect.y = 150;
	} else {
		srcRect.y = 100;
	}

	destRect.x = screenCenterX - 100;
	destRect.y = screenCenterY + 25;

	SDL_RenderCopy(rend, selectionsTexture, &srcRect, &destRect);
}

void MainMenu::renderExit(SDL_Renderer* rend) {
	srcRect.w = destRect.w = 200;
	srcRect.h = destRect.h = 50;

	srcRect.x = 0;
	if (currSelection == EXIT) {
		srcRect.y = 250;
	} else {
		srcRect.y = 200;
	}

	destRect.x = screenCenterX - 100;
	destRect.y = screenCenterY + 75;

	SDL_RenderCopy(rend, selectionsTexture, &srcRect, &destRect);
}

int MainMenu::boundCurrSelection() {
	if (currSelection > EXIT) {
		return GAME_START;
	} else if (currSelection < GAME_START) {
		return EXIT;
	} else {
		return currSelection;
	}
}





