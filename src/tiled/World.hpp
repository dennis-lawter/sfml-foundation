#ifndef WORLD_HPP_
#define WORLD_HPP_
#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "../assets/worlds.hh"

class World {
private:
	const unsigned FLIPPED_HORI = 0x80000000;
	const unsigned FLIPPED_VERT = 0x40000000;
	const unsigned FLIPPED_DIAG = 0x20000000;

	std::string name;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int tileWidth = 0;
	unsigned int tileHeight = 0;

	std::vector<std::vector<sf::Sprite>> tiles;

	void loadFromJson();
public:
	World(std::string name);
	virtual ~World();
};

#endif
