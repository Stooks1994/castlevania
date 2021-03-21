#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <unordered_set>

class Globals {

public:
	Globals();
	virtual ~Globals();

	const static int TILESIZE = 32;
	const static int GRAVITY = 500;
	const static int KEYBOARD_SIZE = 282;

	static void SetRect(SDL_Rect* rect, int x, int y, int w, int h);
	static bool AABB(int, int, int, int, int, int, int, int);
	static bool AABB_1D(int, int, int ,int);
	static bool Contains(std::unordered_set<int> set, int target);

	struct JankTuple {
		int first;
		int second;
		bool third;
	};

	enum Actions { JUMP, LEFT, RIGHT, UP, DOWN, SELECT, QUIT, END };
	enum MouseButton { MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MAX };

};

#endif /* SRC_GLOBALS_H_ */
