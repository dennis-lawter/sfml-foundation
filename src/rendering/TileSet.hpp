#ifndef TILESET_HPP_
#define TILESET_HPP_
#include <SFML/Graphics.hpp>
#include "../assets/assets.hh"

class TileSet : public sf::Sprite {
public:
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int tilesWide = 0;
	unsigned int tilesTall = 0;
	bool flippedHori = false;
	bool flippedVert = false;
	bool flippedDiag = false;

	TileSet(std::string name);

	void setTile(unsigned int x, unsigned int y);

	~TileSet();
};

#endif
