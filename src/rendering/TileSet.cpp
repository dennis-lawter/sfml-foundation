#include "TileSet.hpp"

TileSet::TileSet() {
}

sf::IntRect TileSet::getTileBox(sf::Vector2i coordPair) {
	sf::IntRect rect;
	unsigned int rows = this->tileCount / this->columns;

	rect.left = coordPair.x * this->columns;
	rect.top = coordPair.y * rows;
	rect.width = this->tileWidth;
	rect.height = this->tileHeight;

	return rect;
}

sf::IntRect TileSet::getTileBoxById(unsigned int id) {
	unsigned int idOffset = id - this->firstGid;
	unsigned int rows = this->tileCount / this->columns;
	unsigned int rowSelected = idOffset / rows;
	unsigned int colSelected = idOffset % this->columns;
	sf::Vector2i coordPair (rowSelected, colSelected);
	return this->getTileBox(coordPair);
}

TileSet::~TileSet() {
}
