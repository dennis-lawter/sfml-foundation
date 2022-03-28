#include "Tile.hpp"

Tile::Tile(std::string name) {
	this->setTexture(textures::assets[name]);
}

void Tile::setTileCoordPair(unsigned int x, unsigned int y) {
	
}

Tile::~Tile() {
}
