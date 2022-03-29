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
		// 	this->tilePreDefined.emplace(idIter, tileSetName, this->tileSets[tileSetName]);
		// 	this->tilePreDefined[idIter].setTileFromId(idIter);
		}
	}

	for (auto& layerJson : worldJson["layers"]) {
		if (layerJson["type"] == "tilelayer") {
			nlohmann::json tileData = layerJson["data"];
			for (unsigned int y = 0; y < this->height; y++) {
				for (unsigned int x = 0; x < this->width; x++) {
					unsigned int tileId = tileData[this->width * y + x];
					if (tileId == 0) continue;

					unsigned int tileFlags = (tileId & MOST_SIGNIFICANT_BYTE) >> 24;
					tileId &= THREE_LEAST_SIGNIFICANT_BYTES;

					// bool flipped_horizontally = (tileFlags & FLIPPED_HORI);
					// bool flipped_vertically = (tileFlags & FLIPPED_VERT);
					// bool flipped_diagonally = (tileFlags & FLIPPED_DIAG);
					bool flipped_horizontally = false;
					bool flipped_vertically = false;
					bool flipped_diagonally = false;
					Tile::Rotation tileRotation = Tile::Rotate0;
					if (tileFlags == ROTATED_180D) {
						tileRotation = Tile::Rotate180;
					} else if (tileFlags == ROTATED_090D) {
						tileRotation = Tile::Rotate90;
					} else if (tileFlags == ROTATED_270D) {
						tileRotation = Tile::Rotate270;
					}

					unsigned int tilesIndex = this->tiles.size();
					std::string tileName = this->idToTileNames[tileId];
					// Tile* preDefTile = &(this->tilePreDefined[tileId]);
					// TileSet& tileSetByName = this->tileSets[tileName];
					this->tiles.emplace_back(tileName, this->tileSets[tileName]);
					this->tiles[tilesIndex].flippedHori = flipped_horizontally || flipped_diagonally;
					this->tiles[tilesIndex].flippedVert = flipped_vertically || flipped_diagonally;
					this->tiles[tilesIndex].rotationSelection = tileRotation;
					this->tiles[tilesIndex].setPosition(x * this->tileWidth + this->tileWidth / 2.f, y * this->tileHeight + this->tileHeight / 2.f);
					this->tiles[tilesIndex].setOrigin(this->tileWidth / 2.f, this->tileHeight / 2.f);
					this->tiles[tilesIndex].setTileFromId(tileId);
					this->tiles[tilesIndex].reRender();
					// this->tiles.emplace_back(tile);
				}
			}
		}
	}
}

World::World(std::string name) {
	this->name = name;
	this->loadFromJson();
}

void World::draw(sf::RenderWindow& window) {
	for (Tile& tile : this->tiles) {
		window.draw(tile);
	}
}

World::~World() {
}
