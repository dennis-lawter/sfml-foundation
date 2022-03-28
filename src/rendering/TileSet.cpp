#include "TileSet.hpp"

TileSet::TileSet() {
}

sf::IntRect TileSet::getTileBox(sf::Vector2i coordPair) {
	sf::IntRect rect;
	rect.left = coordPair.x * this->width;
	rect.top = coordPair.y * this->height;
	rect.width = this->width;
	rect.height = this->height;
	return rect;
}

TileSet::~TileSet() {
}
