#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() {
	locked = false;
	running = true;
}

InputManager::~InputManager() {

}

InputManager* InputManager::getInstance() {
	if (!instance)
		instance = new InputManager();

	return instance;
}

void InputManager::update(SDL_Event event) {
	std::unordered_set<SDL_Keycode> tempDown;
	std::unordered_set<SDL_Keycode> tempUp;
	keysDown = tempDown;
	keysUp = tempUp;

	while(SDL_PollEvent(&event) != 0) {
		switch(event.type) {
		case SDL_KEYDOWN: setKeyDown(event.key.keysym.sym); break;
		case SDL_KEYUP: setKeyUp(event.key.keysym.sym); break;
		case SDL_QUIT: running = false; break;

		}
	}
}

std::unordered_set<int> InputManager::getActionsDown() {
	ControlMapper* controls = ControlMapper::getInstance();
	return controls->getActionsFromInput(keysDown);
}

std::unordered_set<int> InputManager::getActionsUp() {
	ControlMapper* controls = ControlMapper::getInstance();
	return controls->getActionsFromInput(keysUp);
}


