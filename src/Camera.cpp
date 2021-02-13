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
	if (yPos < 0) yPos = 0;
}

void Camera::moveCameraX(double xVel, double dt, int mapWidth, int mapHeight) {
	xPos += xVel * dt;

	if (xPos > mapWidth - width) xPos = mapWidth - width;
	if (xPos < 0) xPos = 0;
}

void Camera::moveCameraY(double yVel, double dt, int mapWidth, int mapHeight) {
	yPos += yVel * dt;

	if (yPos > mapHeight - height) yPos = mapHeight - height;
	if (yPos < 0) yPos = 0;
}
