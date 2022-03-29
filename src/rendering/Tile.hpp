#ifndef TILE_HPP_
#define TILE_HPP_
#include <SFML/Graphics.hpp>
#include "../assets/assets.hh"
#include "TileSet.hpp"

class Tile : public sf::Sprite {
public:
	enum Rotation {
		Rotate0 = 0,
		Rotate90 = 1,
		Rotate180 = 2,
		Rotate270 = 3
	};

	std::string name;
	TileSet& tileSet;
	bool flippedHori = false;
	bool flippedVert = false;
	Rotation rotationSelection = Rotate0;

	Tile(std::string name, TileSet& tsRef);
	// Tile(const Tile& copy);

	void setTileFromId(unsigned int id);
	void reRender();

	~Tile();
};

#endif
