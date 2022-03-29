#include "World.hpp"

void World::loadFromJson() {
	std::string jsonFileName = worlds::assets[this->name];
	std::ifstream inStream(jsonFileName);
	nlohmann::json worldJson = nlohmann::json::parse(inStream);

	this->width = worldJson["width"];
	this->height = worldJson["height"];
	this->tileWidth = worldJson["tilewidth"];
	this->tileHeight = worldJson["tileheight"];

	for (auto& tileSetJson : worldJson["tilesets"]) {
		std::string tileSetName = tileSetJson["name"];
		TileSet tileSet;
		tileSet.name = tileSetName;
		tileSet.firstGid = tileSetJson["firstgid"];
		tileSet.tileWidth = tileSetJson["tilewidth"];
		tileSet.tileHeight = tileSetJson["tileheight"];
		tileSet.columns = tileSetJson["columns"];
		tileSet.tileCount = tileSetJson["tilecount"];
		this->tileSets.emplace(tileSetName, tileSet);

		unsigned int finalGid = tileSet.firstGid + tileSet.tileCount;
		for (unsigned int idIter = tileSet.firstGid; idIter < finalGid; idIter++) {
			this->idToTileNames[idIter] = tileSetName;
		}
	}

	for (auto& layerJson : worldJson["layers"]) {
		if (layerJson["type"] == "tilelayer") {
			if (layerJson["name"] == "collision") {
				nlohmann::json tileData = layerJson["data"];
				for (unsigned int y = 0; y < this->height; y++) {
					for (unsigned int x = 0; x < this->width; x++) {
						unsigned int tileId = tileData[this->width * y + x];
						if (tileId == 0) continue;
						sf::IntRect collisionTile;
						collisionTile.left = x * this->tileWidth;
						collisionTile.top = y * this->tileHeight;
						collisionTile.width = this->tileWidth;
						collisionTile.height = this->tileHeight;
						this->staticCollision.emplace_back(collisionTile);
					}
				}
			} else {
				nlohmann::json tileData = layerJson["data"];
				float opacity = layerJson["opacity"];
				sf::Color color = sf::Color::White;
				color.a = opacity * 255;
				for (unsigned int y = 0; y < this->height; y++) {
					for (unsigned int x = 0; x < this->width; x++) {
						unsigned int tileId = tileData[this->width * y + x];
						if (tileId == 0) continue;

						unsigned char tileFlags = (tileId & MOST_SIGNIFICANT_BYTE) >> 24;
						tileId &= THREE_LEAST_SIGNIFICANT_BYTES;

						unsigned int tilesIndex = this->tiles.size();
						std::string tileName = this->idToTileNames[tileId];
						this->tiles.emplace_back(tileName, this->tileSets[tileName]);
						this->tiles[tilesIndex].transformation = (Tile::Transformation)tileFlags;
						this->tiles[tilesIndex].setPosition(x * this->tileWidth + this->tileWidth / 2.f, y * this->tileHeight + this->tileHeight / 2.f);
						this->tiles[tilesIndex].setOrigin(this->tileWidth / 2.f, this->tileHeight / 2.f);
						this->tiles[tilesIndex].setTileFromId(tileId);
						this->tiles[tilesIndex].performTransformations();
						this->tiles[tilesIndex].setColor(color);
					}
				}
			}
		} else if (layerJson["type"] == "objectgroup") {
			for (nlohmann::json& objectJson : layerJson["objects"]) {
				std::string objectName = objectJson["name"];
				unsigned int id = objectJson["id"];
				float x = objectJson["x"];
				float y = objectJson["y"];

				this->objs[id] = new GameObject(objectName);
				sf::FloatRect rect = this->objs[id]->getHitBox();
				// adjust for tilded using bottom left px origin
				x += rect.width/2.f;
				y -= rect.width/2.f;
				this->objs[id]->setPosition(sf::Vector2f(x, y));
			}
		}
	}
}

World::World(std::string name) {
	this->name = name;
	this->loadFromJson();
}

void World::update() {
	for (auto& [key, objPtr]: this->objs) {
		objPtr->update();
	}
}

void World::draw(sf::RenderWindow& window) {
	for (Tile& tile : this->tiles) {
		window.draw(tile);
	}
	for (const auto& [key, objPtr]: this->objs) {
		objPtr->draw(window);
	}
}

World::~World() {
	for (auto& [key, objPtr]: this->objs) {
		delete objPtr;
	}
}
