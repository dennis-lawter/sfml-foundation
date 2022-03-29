#ifndef WORLD_HPP_
#define WORLD_HPP_
#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "../assets/worlds.hh"
#include "../rendering/Tile.hpp"

class World {
private:
	const unsigned char FLIPPED_HORI = 0x80;
	const unsigned char FLIPPED_VERT = 0x40;
	const unsigned char FLIPPED_DIAG = 0x20;
	const unsigned char ROTATED_090D = 0xA0;
	const unsigned char ROTATED_180D = 0xC0;
	const unsigned char ROTATED_270D = 0x60;
	const unsigned int MOST_SIGNIFICANT_BYTE = 0xFF000000;
	const unsigned int THREE_LEAST_SIGNIFICANT_BYTES = 0x00FFFFFF;

	std::string name;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int tileWidth = 0;
	unsigned int tileHeight = 0;

	std::vector<Tile> tiles;
	// std::map<unsigned int, Tile> tilePreDefined;
	std::map<unsigned int, std::string> idToTileNames;
	std::map<std::string, TileSet> tileSets;

	void loadFromJson();
public:
	World(std::string name);
	virtual ~World();
};

#endif
