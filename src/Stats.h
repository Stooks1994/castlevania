#ifndef SRC_STATS_H_
#define SRC_STATS_H_

class Stats {

public:
	Stats();
	Stats(double _xVel,
			double _yVel,
			double _xPos,
			double _yPos,
			double _movespeed,
			double _jumpForce,
			double _jumpForceMax,
			double _jumpDampening,
			int _height,
			int _width);

	virtual ~Stats();

	double getXVel() { return xVel; };
	double getYVel() { return yVel; };
	double getXPos() { return xPos; };
	double getYPos() { return yPos; };
	double getMovespeed() { return movespeed; };
	double getJumpForce() { return jumpForce; };
	double getJumpForceMax() { return jumpForceMax; };
	double getJumpDampening() { return jumpDampening; };

	int getHeight() { return height; };
	int getWidth() { return width; };

	void setXVel(double value) { xVel = value; };
	void setYVel(double value) { yVel = value; };
	void setXPos(double value) { xPos = value; };
	void setYPos(double value) { yPos = value; };
	void setMovespeed(double value) { movespeed = value; };
	void setJumpForce(double value) { jumpForce = value; };
	void setJumpForceMax(double value) { jumpForceMax = value; };
	void setJumpDampening(double value) { jumpDampening = value; };
	void setHeight(int value) { height = value; };
	void setWidth(int value) { width = value; };

	void incrementXPos(double value) { xPos += value; };
	void incrementYPos(double value) { yPos += value; };
	void incrementXVel(double value) { xVel += value; };
	void incrementYVel(double value) { yVel += value; };

private:
	double xVel;
	double yVel;
	double xPos;
	double yPos;
	double movespeed;
	double jumpForce;
	double jumpForceMax;
	double jumpDampening;

	int height;
	int width;
};

#endif /* SRC_STATS_H_ */
