#include "TileSet.hpp"

TileSet::TileSet(std::string name) {
	this->setTexture(textures::assets[name]);
}

void TileSet::setTile(unsigned int x, unsigned int y) {
	
}

TileSet::~TileSet() {
}
