#include "Tile.hpp"

Tile::Tile(std::string name, TileSet& tsRef)
	: tileSet(tsRef) {
	this->name = name;
	this->setTexture(textures::assets[name]);
}

// Tile::Tile(const Tile& copy)
// 	: tileSet(copy.tsRef)
// 	, Sprite(copy) {
// 	bool flippedHori = copy.flippedHori;
// 	bool flippedVert = copy.flippedVert;
// 	Rotation rotationSelection = copy.rotationSelection;
// 	this->setTexture(this->name);
// }

void Tile::setTileFromId(unsigned int id) {
	sf::IntRect tileBox = this->tileSet.getTileBoxById(id);
	this->setTextureRect(tileBox);
}

void Tile::reRender() {
	if (this->flippedHori) {
		this->scale(-1.f, 1.f);
	}
	if (this->flippedVert) {
		this->scale(1.f, -1.f);
	}
	this->setRotation(this->rotationSelection * 90.f);
}

Tile::~Tile() {
}
