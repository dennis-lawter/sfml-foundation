#ifndef WORLD_HPP_
#define WORLD_HPP_
#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "../assets/worlds.hh"
#include "../rendering/Tile.hpp"
#include "../gameObj/GameObjectFactory.hh"

class World {
private:
	const unsigned int MOST_SIGNIFICANT_BYTE = 0xFF000000;
	const unsigned int THREE_LEAST_SIGNIFICANT_BYTES = 0x00FFFFFF;

	std::string name;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int tileWidth = 0;
	unsigned int tileHeight = 0;

	std::map<unsigned int, std::string> idToTileNames;
	std::map<std::string, TileSet> tileSets;
	
	std::vector<Tile> tiles;
	std::vector<sf::IntRect> staticCollision;
	std::map<unsigned int, GameObject*> objs;

	void loadFromJson();
public:
	World(std::string name);

	void update();
	void draw(sf::RenderWindow& window);

	virtual ~World();
};

#endif
