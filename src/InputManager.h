#ifndef SRC_INPUTMANAGER_H_
#define SRC_INPUTMANAGER_H_

#include "Globals.h"

class InputManager {

public:
	InputManager();
	virtual ~InputManager();

	void setFlag(int flag) { actionFlags[flag] = 1; };
	void unsetFlag(int flag) { actionFlags[flag] = 0; };


private:
	int actionFlags[Globals::END];
};

#endif /* SRC_INPUTMANAGER_H_ */
