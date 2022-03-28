#include "tilesets.hh"
#include <iostream>

namespace tilesets {
	std::map<std::string, std::string> assets;
	bool loaded = false;
	std::thread loadingThread;

	const std::string META_FILE = "resource/meta/tilesets.json";

	void performLoading() {
		std::ifstream inStream (tilesets::META_FILE, std::ifstream::in);
		nlohmann::json jsonData = nlohmann::json::parse(inStream);

		for (auto& animationDefinition : jsonData.items()) {
			std::string key = animationDefinition.key();
			nlohmann::json data = animationDefinition.value();
			// std::string defaultAnimation = data["defaultAnimation"];
			// unsigned int width = data["width"];
			// unsigned int height = data["height"];
			// unsigned int framesPer = data["framesPer"];
			// nlohmann::json tilesetsJsonList = data["tilesets"];
			// tilesets::assets.emplace(key, AnimationList{});
			// tilesets::assets[key].width = width;
			// tilesets::assets[key].height = height;
			// tilesets::assets[key].framesPer = framesPer;
			// tilesets::assets[key].textureName = key;
			// tilesets::assets[key].defaultAnimation = defaultAnimation;
			// for (auto& animationJson : tilesetsJsonList.items()) {
			// 	std::string animationName = animationJson.key();
			// 	nlohmann::json animationArray = animationJson.value();
			// 	tilesets::assets[key].createEmptyList(animationName);
			// 	for (auto& animationCoords : animationArray) {
			// 		sf::Vector2i coordPair;
			// 		coordPair.x = animationCoords[0];
			// 		coordPair.y = animationCoords[1];
			// 		tilesets::assets[key].appendToList(animationName, coordPair);
			// 	}
			// }
		}

		tilesets::loaded = true;
	}

	void load() {
		tilesets::loadingThread = std::thread(performLoading);
		tilesets::loadingThread.detach();
	}

	void unload() {
		tilesets::loaded = false;
		if (tilesets::loadingThread.joinable()) {
			tilesets::loadingThread.join();
		}
		tilesets::assets.clear();
	}
}
