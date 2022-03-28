#ifndef TILESET_HPP_
#define TILESET_HPP_
#include <SFML/Graphics/Rect.hpp>

class TileSet {
public:
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int tilesWide = 0;
	unsigned int tilesTall = 0;

	TileSet();

	sf::IntRect getTileBox(sf::Vector2i coordPair);

	virtual ~TileSet();
};

#endif
