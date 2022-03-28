#ifndef TILE_HPP_
#define TILE_HPP_
#include <SFML/Graphics.hpp>
#include "../assets/assets.hh"

class Tile : public sf::Sprite {
public:
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int tilesWide = 0;
	unsigned int tilesTall = 0;
	bool flippedHori = false;
	bool flippedVert = false;
	bool flippedDiag = false;

	Tile(std::string name);

	void setTileCoordPair(unsigned int x, unsigned int y);

	~Tile();
};

#endif
