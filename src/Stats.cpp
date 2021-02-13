#include "Stats.h"

Stats::Stats() {
	xVel = yVel = xPos = yPos = movespeed = jumpForce = jumpForceMax = jumpDampening = 0;
	height = width = 0;
}

Stats::Stats(double _xVel, double _yVel, double _xPos, double _yPos, double _movespeed,
		double _jumpForce, double _jumpForceMax, double _jumpDampening,
		int _height, int _width) {
	xVel = _xVel;
	yVel = _yVel;
	xPos = _xPos;
	yPos = _yPos;
	movespeed = _movespeed;
	jumpForce = _jumpForce;
	jumpForceMax = _jumpForceMax;
	jumpDampening = _jumpDampening;
	height = _height;
	width = _width;
}

Stats::~Stats() {

}

