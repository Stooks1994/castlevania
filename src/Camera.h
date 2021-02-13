#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

class Camera {

public:
	Camera(double xPosition, double yPosition, int w, int h);
	virtual ~Camera();

	void moveCamera(double xVel, double yVel, double dt, int mapWidth, int mapHeight);
	void moveCameraX(double, double, int, int);
	void moveCameraY(double, double, int, int);

	double xPos;
	double yPos;

	int height;
	int width;
};

#endif /* SRC_CAMERA_H_ */
