#include "LevelLoader.h"

LevelLoader::LevelLoader(const char* _srcFile) {
	srcFile = _srcFile;
	levelWidth = levelHeight = mapLineNumber = 0;
	header = SETTINGS;

	tileset = NULL;
	backgroundTexture = NULL;

	loadLevelFromFile();
}

LevelLoader::~LevelLoader() {
	// TODO Auto-generated destructor stub
}

void LevelLoader::loadLevelFromFile() {
	try {
		std::ifstream levelStream(srcFile, std::ios_base::in);
		std::string line;

		printf("Opened file\n");

		while (getline(levelStream, line)) {
			line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

			if (!parseHeader(line)) {
				switch(header) {
				case SETTINGS:
					parseSettings(line);
					break;
				case LEGEND:
					parseLegend(line);
					break;
				case MAP:
					mapLineNumber = parseMap(line);
					break;
				case ENEMIES:
					parseEnemies(line);
					break;
				case END:
					parseEnd();
					break;
				}
			}
		}

		levelStream.close();
	} catch (int e) {
		printf("Failed load file\n");
	}
}

bool LevelLoader::parseHeader(std::string _header) {
	if (_header.find("~") != std::string::npos) {
		_header = _header.substr(_header.find("~") + 1);

		if (_header.compare("SETTINGS") == 0)
			header = SETTINGS;
		else if (_header.compare("LEGEND") == 0)
			header = LEGEND;
		else if (_header.compare("MAP") == 0)
			header = MAP;
		else if (_header.compare("ENEMIES") == 0)
			header = ENEMIES;
		else if (_header.compare("END") == 0)
			header = END;

		return true;
	} else {
		return false;
	}
}

void LevelLoader::parseSettings(std::string _line) {
	std::string delimiter = "=";
	std::string property = _line.substr(0, _line.find(delimiter));
	std::string value = _line.substr(_line.find(delimiter) + 1);

	if (property.compare("tileset") == 0)
		tileset = TextureManager::loadTexture(value.c_str());
	else if (property.compare("background") == 0)
		backgroundTexture = TextureManager::loadTexture(value.c_str());
}

void LevelLoader::parseLegend(std::string _line) {
	if (!_line.empty()) {
		std::string delimiter = "=";
		std::string property = _line.substr(0, _line.find(delimiter));
		std::string value = _line.substr(_line.find(delimiter) + 1);

		//if (value.compare("GRASS") == 0)
		//printf("In parseLegend %s %s\n", property.c_str(), value.c_str());
		//legend[property] = TextureManager::loadTexture(value.c_str());
		legend[property] = tileset;
	}
}

int LevelLoader::parseMap(std::string _line) {
	for (int column = 0; column < _line.length(); column++) {
		char& currChar = _line.at(column);
		std::string currStr = "";
		currStr.push_back(currChar);
		SDL_Texture* tex = legend.at(currStr);

		Globals::Tile* tile = new Globals::Tile{
			Globals::TILESIZE * column,
			Globals::TILESIZE * mapLineNumber,
			tex
		};

		tiles.push_back(tile);
	}

	return mapLineNumber + 1;
}

void LevelLoader::parseEnemies(std::string _line) {

}

void LevelLoader::parseEnd() {

}
