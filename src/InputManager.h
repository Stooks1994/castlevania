#ifndef SRC_INPUTMANAGER_H_
#define SRC_INPUTMANAGER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Globals.h"
#include "ControlMapper.h"

#include <unordered_map>
#include <unordered_set>
#include <string>

class InputManager {

public:
	InputManager();
	virtual ~InputManager();

	static InputManager* getInstance();

	std::unordered_set<int> getActionsDown();
	std::unordered_set<int> getActionsUp();

	bool isLocked() { return locked; };
	bool isRunning() { return running; };

	void update(SDL_Event event);
	void lock() { locked = true; };
	void unlock() { locked = false; };

private:
	static InputManager* instance;

	std::unordered_set<SDL_Keycode> keysDown;
	std::unordered_set<SDL_Keycode> keysUp;

	bool running;
	bool locked;

	void setKeyDown(SDL_Keycode key) { keysDown.insert(key); };
	void setKeyUp(SDL_Keycode key) { keysUp.insert(key); };
	std::unordered_set<SDL_Keycode> getDownKeys() { return keysDown; };
	std::unordered_set<SDL_Keycode> getUpKeys() { return keysUp; };
};

#endif /* SRC_INPUTMANAGER_H_ */
