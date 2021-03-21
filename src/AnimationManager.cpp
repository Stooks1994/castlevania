#include "AnimationManager.h"

AnimationManager::AnimationManager() {
	animationTimer = 0;
}

AnimationManager::~AnimationManager() {
	// TODO Auto-generated destructor stub
}

void AnimationManager::updateTimer(double dt) {
	animationTimer += dt;

	if (animationTimer > 1) {
		animationTimer = 0;
	}
}
