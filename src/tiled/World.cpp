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
						float tileX = x * this->tileWidth + this->tileWidth / 2.f;
						float tileY = y * this->tileHeight + this->tileHeight / 2.f;
						this->tiles[tilesIndex].setPosition(tileX, tileY);
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

				this->objs[id] = GameObjectFactory::create(objectName);
				if (objectName == "player") {
					this->playerPtr = (Player*)this->objs[id];
					this->camera.setFollowedObject(this->playerPtr);
				}

				sf::FloatRect rect = this->objs[id]->getHitBox();
				// adjust for tilded using bottom left px origin
				x += rect.width / 2.f;
				y -= rect.width / 2.f;
				this->objs[id]->setPosition(sf::Vector2f(x, y));

				if (objectJson.contains("properties")) {
					for (nlohmann::json& propertyJson : objectJson["properties"]) {
						std::string propertyType = propertyJson["type"];
						std::string propertyName = propertyJson["name"];
						if (propertyType == "int" || propertyType == "object") {
							this->objs[id]->setCustomProperty(propertyName, (int)propertyJson["value"]);
						} else if (propertyType == "color") {
							this->objs[id]->setCustomProperty(propertyName, (unsigned int)propertyJson["value"]);
						} else if (propertyType == "bool") {
							this->objs[id]->setCustomProperty(propertyName, (bool)propertyJson["value"]);
						} else if (propertyType == "float") {
							this->objs[id]->setCustomProperty(propertyName, (float)propertyJson["value"]);
						} else {
							this->objs[id]->setCustomProperty(propertyName, (std::string)propertyJson["value"]);
						}
					}
				}
			}
		}
	}
}

World::World(std::string name, sf::RenderWindow& window)
	: window(window) {
	this->name = name;
	this->loadFromJson();
	this->background.setFillColor(sf::Color::Black);
	this->background.setPosition(-defines::WIDTH, -defines::HEIGHT);
	int bgWidth = this->width * this->tileWidth + defines::WIDTH * 2;
	int bgHeight = this->height * this->tileHeight + defines::HEIGHT * 2;
	this->background.setSize(sf::Vector2f(bgWidth, bgHeight));
	this->camera.setWindow(&window);
}

void World::testCollision() {
	for ([[maybe_unused]] auto& [key, objPtr] : this->objs) {
		sf::Vector2f idealPosition = objPtr->getPosition();
		sf::Vector2f oldPos = objPtr->oldPosition;
		objPtr->setPosition(sf::Vector2f(idealPosition.x, oldPos.y));
		for (sf::FloatRect& t : this->staticCollision) {
			if (objPtr->testCollision(t)) {
				objPtr->setPosition(oldPos);
				break;
			}
		}
		sf::Vector2f temp = objPtr->getPosition();
		objPtr->setPosition(sf::Vector2f(temp.x, idealPosition.y));
		for (sf::FloatRect& t : this->staticCollision) {
			if (objPtr->testCollision(t)) {
				objPtr->setPosition(sf::Vector2f(temp.x, oldPos.y));
				if (objPtr->name == "player") {
					Player* asPlayer = (Player*)objPtr;
					asPlayer->velocity.y = 0.f;
					asPlayer->canJump = true;
				}
				break;
			}
		}
	}
}

void World::snap(GameObject& subject, sf::Vector2f currentPosition, sf::Vector2f oldPosition, sf::FloatRect& target) {
	float subjectWidth = subject.getWidth();
	float subjectHeight = subject.getHeight();
	float targetWidth = target.width;
	float targetHeight = target.height;

	sf::Vector2f targetPosition = { target.left, target.top };
	sf::Vector2f distance = currentPosition - oldPosition;
	if (distance.x < -defines::precisionRounding) {
		//right collision
		currentPosition.x = (targetPosition.x + targetWidth + defines::precisionRounding + subjectWidth / 2.f);
	} else if (distance.x > defines::precisionRounding) {
		//left collision
		currentPosition.x = (targetPosition.x - defines::precisionRounding - subjectWidth / 2.f);
	} else if (distance.y < -defines::precisionRounding) {
		//top collision
		currentPosition.y = (targetPosition.y + targetHeight + defines::precisionRounding + subjectHeight / 2.f);
	} else if (distance.y > defines::precisionRounding) {
		//bottom collision
		currentPosition.y = (targetPosition.y - defines::precisionRounding - subjectHeight / 2.f);
	}

	subject.setPosition(currentPosition);
}

void World::update() {
	for (auto& [key, objPtr] : this->objs) {
		objPtr->update();
	}
	testCollision();
}

void World::draw() {
	if (this->playerPtr) {
		sf::View view = window.getView();
		view.setCenter(this->playerPtr->getPosition());
		window.setView(view);
	}
	this->window.draw(background);
	for (Tile& tile : this->tiles) {
		window.draw(tile);
	}
	for (const auto& [key, objPtr] : this->objs) {
		objPtr->draw(window);
	}
}

World::~World() {
	for (auto& pair : this->objs) {
		GameObjectFactory::destroy(pair.second);
	}
}
