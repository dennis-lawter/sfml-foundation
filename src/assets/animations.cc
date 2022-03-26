#include "animations.hh"
#include <iostream>

namespace animations {
	std::map<std::string, AnimationList> assets;
	bool loaded = false;
	std::thread loadingThread;

	const std::string ANIMATIONS_META_FILE = "resource/meta/animations.json";

	void performLoading() {
		std::ifstream inStream (animations::ANIMATIONS_META_FILE, std::ifstream::in);
		nlohmann::json jsonData = nlohmann::json::parse(inStream);

		for (auto& animationDefinition : jsonData.items()) {
			std::string key = animationDefinition.key();
			nlohmann::json data = animationDefinition.value();
			unsigned int width = data["width"];
			unsigned int height = data["height"];
			unsigned int framesPer = data["framesPer"];
			nlohmann::json animationsJsonList = data["animations"];
			animations::assets.emplace(key, AnimationList{});
			animations::assets[key].width = width;
			animations::assets[key].height = height;
			animations::assets[key].framesPer = framesPer;
			animations::assets[key].textureName = key;
			for (auto& animationJson : animationsJsonList.items()) {
				std::string animationName = animationJson.key();
				nlohmann::json animationArray = animationJson.value();
				animations::assets[key].createEmptyList(animationName);
				for (auto& animationCoords : animationArray) {
					sf::Vector2i coordPair;
					coordPair.x = animationCoords[0];
					coordPair.y = animationCoords[1];
					animations::assets[key].appendToList(animationName, coordPair);
				}
			}
		}

		animations::loaded = true;
	}

	void load() {
		animations::loadingThread = std::thread(performLoading);
		animations::loadingThread.detach();
	}

	void unload() {
		animations::loaded = false;
		if (animations::loadingThread.joinable()) {
			animations::loadingThread.join();
		}
		animations::assets.clear();
	}
}
