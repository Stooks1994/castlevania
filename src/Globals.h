#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Globals {

public:
	Globals();
	virtual ~Globals();

	const static int TILESIZE = 32;
	const static int GRAVITY = 500;

	static void SetRect(SDL_Rect* rect, int x, int y, int w, int h);
	static bool AABB(int, int, int, int, int, int, int, int);
	static bool AABB_1D(int, int, int ,int);

	struct JankTuple {
		int first;
		int second;
		bool third;
	};
};

#endif /* SRC_GLOBALS_H_ */
