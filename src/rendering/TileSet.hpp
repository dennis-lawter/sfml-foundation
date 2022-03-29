#ifndef TILESET_HPP_
#define TILESET_HPP_
#include <SFML/Graphics/Rect.hpp>

class TileSet {
public:
	std::string name = "";
	unsigned int firstGid = 0;
	unsigned int tileWidth = 0;
	unsigned int tileHeight = 0;
	unsigned int columns = 0;
	unsigned int tileCount = 0;

	TileSet();

	sf::IntRect getTileBox(sf::Vector2i coordPair);
	sf::IntRect getTileBoxById(unsigned int id);

	virtual ~TileSet();
};

#endif
