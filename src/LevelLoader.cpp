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
	else if (property.compare("indices") == 0) {
		populateIndices(value);
	}
}

void LevelLoader::parseLegend(std::string _line) {
	if (!_line.empty()) {
		std::string delimiter = "=";
		std::string property = _line.substr(0, _line.find(delimiter));
		std::string value = _line.substr(_line.find(delimiter) + 1);

		legend[property] = value;
	}
}

int LevelLoader::parseMap(std::string _line) {
	for (int column = 0; column < _line.length(); column++) {
		char& currChar = _line.at(column);
		std::string currStr = "";
		currStr.push_back(currChar);
		std::string legendValue = legend[currStr];

		if (legendValue.compare("BACKGROUND") != 0) {
			Tile* tile = new Tile(
				Globals::TILESIZE * column,
				Globals::TILESIZE * mapLineNumber,
				indices[legendValue]->first * Globals::TILESIZE,
				indices[legendValue]->second * Globals::TILESIZE,
				indices[legendValue]->third,
				tileset
			);

			tiles.push_back(tile);
		}
	}

	return mapLineNumber + 1;
}

void LevelLoader::parseEnemies(std::string _line) {

}

void LevelLoader::parseEnd() {

}

void LevelLoader::populateIndices(std::string _value) {
	std::regex indexRegex("\\((\\w+),([0-9]+),([0-9]+),(\\w+)\\)");

	auto begin = std::sregex_iterator(_value.begin(), _value.end(), indexRegex);
	auto end = std::sregex_iterator();

	for (std::sregex_iterator i = begin; i != end; ++i) {
		std::smatch match = *i;
		indices[match.str(1)] = new Globals::JankTuple { stoi(match.str(2)), stoi(match.str(3)), stob(match.str(4)) };
	}
}

bool LevelLoader::stob(std::string val) {
	if (val.compare("TRUE") == 0) {
		return true;
	}

	return false;
}
