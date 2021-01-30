#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Globals {

public:
	Globals();
	virtual ~Globals();

	const static int TILESIZE = 32;

	static void set_rect(SDL_Rect* rect, int x, int y, int w, int h);
};

#endif /* SRC_GLOBALS_H_ */
