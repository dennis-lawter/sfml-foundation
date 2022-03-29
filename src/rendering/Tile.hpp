#ifndef TILE_HPP_
#define TILE_HPP_
#include <SFML/Graphics.hpp>
#include "../assets/assets.hh"
#include "TileSet.hpp"

class Tile : public sf::Sprite {
public:
	enum Transformation : unsigned char {
		NO_TRANSFORM = 0x00, // 00000000
		FLIPPED_DIAG = 0x20, // 00100000
		FLIPPED_VERT = 0x40, // 01000000
		ROTATED_270D = 0x60, // 01100000
		FLIPPED_HORI = 0x80, // 10000000
		ROTATED_090D = 0xA0, // 10100000
		ROTATED_180D = 0xC0, // 11000000
		TRIPLE_TRANS = 0xE0  // 11100000
	};

	std::string name;
	TileSet& tileSet;
	Transformation transformation;

	Tile(std::string name, TileSet& tsRef);

	void setTileFromId(unsigned int id);
	void performTransformations();

	~Tile();
};

#endif
