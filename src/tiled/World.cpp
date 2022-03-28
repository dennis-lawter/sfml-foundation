#include "World.hpp"

void World::loadFromJson() {
	std::string jsonFileName = worlds::assets[this->name];
	std::ifstream inStream (jsonFileName);
	nlohmann::json worldJson = nlohmann::json::parse(inStream);

	this->width = worldJson["width"];
	this->height = worldJson["height"];
	this->tileWidth = worldJson["tileWidth"];
	this->tileHeight = worldJson["tileHeight"];

	for (auto& layer : worldJson["layers"]) {
		if (layer["type"] == "tilelayer") {
			nlohmann::json tileData = layer["data"];
			for (unsigned int y = 0; y < this->height; y++) {
				for (unsigned int x = 0; x < this->width; x++) {
					unsigned int tileId = tileData[this->width * y + x];
					bool flipped_horizontally = (tileId & FLIPPED_HORI);
					bool flipped_vertically = (tileId & FLIPPED_VERT);
					bool flipped_diagonally = (tileId & FLIPPED_DIAG);

					tileId &= ~FLIPPED_HORI;
					tileId &= ~FLIPPED_VERT;
					tileId &= ~FLIPPED_DIAG;
				}
			}
		}
	}
}

World::World(std::string name) {
	this->name = name;
}

World::~World() {
}
