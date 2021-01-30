#include "Globals.h"

Globals::Globals() {

}

Globals::~Globals() {

}

void Globals::set_rect(SDL_Rect* rect, int x, int y, int w, int h) {
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

