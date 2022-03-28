#include "Tile.hpp"

Tile::Tile(std::string name) {
	this->tileset = &(tilesets::assets[name]);
	this->setTexture(textures::assets[name]);
}

void Tile::setTileCoordPair(sf::Vector2i coordPair) {
	sf::IntRect tileBox = this->tileset->getTileBox(coordPair);
	this->setTextureRect(tileBox);
}

Tile::~Tile() {
}
