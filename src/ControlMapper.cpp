#include "ControlMapper.h"

ControlMapper* ControlMapper::instance = nullptr;

ControlMapper::ControlMapper() {
	defaultControlMap = {
			{ SDLK_a, Globals::LEFT },
			{ SDLK_d, Globals::RIGHT },
			{ SDLK_w, Globals::UP },
			{ SDLK_s, Globals::DOWN },
			{ SDLK_SPACE, Globals::JUMP },
			{ SDLK_RETURN, Globals::SELECT }
	};

	controlMap = defaultControlMap;
}

ControlMapper::~ControlMapper() {
	// TODO Auto-generated destructor stub
}

ControlMapper* ControlMapper::getInstance() {
	if (!instance)
		instance = new ControlMapper();

	return instance;
}

std::unordered_set<int> ControlMapper::getActionsFromInput(std::unordered_set<SDL_Keycode> input) {
	std::unordered_set<int> actions;

	for (auto& in : input) {
		actions.insert(controlMap[in]);
	}

	return actions;
}

