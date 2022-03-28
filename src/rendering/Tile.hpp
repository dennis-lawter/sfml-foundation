#ifndef TILE_HPP_
#define TILE_HPP_
#include <SFML/Graphics.hpp>
#include "../assets/assets.hh"

class Tile : public sf::Sprite {
public:
	enum Rotation {
		Rotate0 = 0,
		Rotate90 = 1,
		Rotate180 = 2,
		Rotate270 = 3
	};
	TileSet* tileset;
	bool flippedHori = false;
	bool flippedVert = false;
	Rotation rotationDegrees = Rotate0;

	Tile(std::string name);

	void setTileCoordPair(sf::Vector2i coordPair);

	~Tile();
};

#endif
