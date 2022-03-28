#include "textures.hh"
#include <iostream>

namespace textures {
	std::map<std::string, sf::Texture> assets;
	bool loaded = false;
	std::thread loadingThread;

	const std::string META_FILE = "resource/meta/textures.json";

	void performLoading() {
		std::ifstream inStream (textures::META_FILE, std::ifstream::in);
		nlohmann::json textureJson = nlohmann::json::parse(inStream);
		
		for (auto& textureDefinition : textureJson.items()) {
			std::string key = textureDefinition.key();
			nlohmann::json data = textureDefinition.value();
			std::string dataFile = data["file"];
			textures::assets.emplace(key, sf::Texture{});
			textures::assets[key].loadFromFile(dataFile);
		}

		textures::loaded = true;
	}

	void load() {
		textures::loadingThread = std::thread(performLoading);
		textures::loadingThread.detach();
	}

	void unload() {
		textures::loaded = false;
		if (textures::loadingThread.joinable()) {
			textures::loadingThread.join();
		}
		textures::assets.clear();
	}
}
