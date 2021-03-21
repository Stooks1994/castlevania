#ifndef SRC_ANIMATIONMANAGER_H_
#define SRC_ANIMATIONMANAGER_H_

class AnimationManager {

public:
	AnimationManager();
	virtual ~AnimationManager();

	void updateTimer(double dt);

private:
	double animationTimer;
};

#endif /* SRC_ANIMATIONMANAGER_H_ */
