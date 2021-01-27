#include "Camera.h"

Camera::Camera(double xPosition, double yPosition, int w, int h) {
	xPos = xPosition;
	yPos = yPosition;
	width = w;
	height = h;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::moveCamera(double xVel, double yVel, double dt, int mapWidth, int mapHeight) {
	xPos += xVel * dt;
	yPos += yVel * dt;

	if (xPos > mapWidth - width) xPos = mapWidth - width;
	if (xPos < 0) xPos = 0;

	if (yPos > mapHeight - height) yPos = mapHeight - height;
	if (xPos < 0) xPos = 0;
}
