#include "Tile.hpp"

Tile::Tile(std::string name, TileSet& tsRef)
	: tileSet(tsRef) {
	this->name = name;
	this->setTexture(textures::assets[name]);
}

void Tile::setTileFromId(unsigned int id) {
	sf::IntRect tileBox = this->tileSet.getTileBoxById(id);
	this->setTextureRect(tileBox);
}

void Tile::performTransformations() {
	switch (this->transformation) {
	case Tile::TRIPLE_TRANS:
		this->setRotation(90.f);
		this->setScale(-1.f, 1.f);
		break;
	case Tile::ROTATED_180D:
		this->setRotation(180.f);
		this->setScale(1.f, 1.f);
		break;
	case Tile::ROTATED_090D:
		this->setRotation(90.f);
		this->setScale(1.f, 1.f);
		break;
	case Tile::FLIPPED_HORI:
		this->setRotation(0.f);
		this->setScale(-1.f, 1.f);
		break;
	case Tile::ROTATED_270D:
		this->setRotation(270.f);
		this->setScale(1.f, 1.f);
		break;
	case Tile::FLIPPED_VERT:
		this->setRotation(0.f);
		this->setScale(1.f, -1.f);
		break;
	case Tile::FLIPPED_DIAG:
		this->setRotation(270.f);
		this->setScale(-1.f, 1.f);
		break;
	case Tile::NO_TRANSFORM:
	default:
		this->setRotation(0.f);
		this->setScale(1.f, 1.f);
		break;
	}
}

Tile::~Tile() {
}
