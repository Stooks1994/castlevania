#ifndef SRC_LEVELLOADER_H_
#define SRC_LEVELLOADER_H_

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <regex>
#include <tuple>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.h"
#include "Globals.h"
#include "Tile.h"

class LevelLoader {

public:
	LevelLoader(const char* srcFile);
	virtual ~LevelLoader();

	void loadLevelFromFile();

	SDL_Texture* getBackgroundTexture() { return backgroundTexture; };
	std::vector<Tile*> getTiles() { return tiles; };

	enum Headers { SETTINGS, LEGEND, MAP, ENEMIES, END };

private:
	const char* srcFile;

	std::unordered_map<std::string, std::string> legend;
	std::unordered_map<std::string, Globals::JankTuple*> indices;
	std::vector<Tile*> tiles;

	SDL_Texture* tileset;
	SDL_Texture* backgroundTexture;

	int mapLineNumber;
	int levelWidth;
	int levelHeight;
	int header;

	bool parseHeader(std::string);
	void parseSettings(std::string);
	void parseLegend(std::string);
	int parseMap(std::string);
	void parseEnemies(std::string);
	void parseEnd();

	void populateIndices(std::string);

	bool stob(std::string);
};

#endif /* SRC_LEVELLOADER_H_ */
