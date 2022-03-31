#ifndef WORLD_HPP_
#define WORLD_HPP_
#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "../assets/worlds.hh"
#include "../rendering/Tile.hpp"
#include "../rendering/Camera.hpp"
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
	sf::RenderWindow& window;
	sf::RectangleShape background;

	std::map<unsigned int, std::string> idToTileNames;
	std::map<std::string, TileSet> tileSets;

	std::vector<Tile> tiles;
	std::vector<sf::FloatRect> staticCollision;
	std::map<unsigned int, GameObject*> objs;

	Player* playerPtr = nullptr;

	Camera camera;

	void loadFromJson();
	void testCollision();
	void snap(GameObject &subject, sf::Vector2f currentPosition, sf::Vector2f oldPosition, sf::FloatRect &target);
public:
	World(std::string name, sf::RenderWindow& window);

	void update();
	void draw();

	virtual ~World();
};

#endif
