#include "fonts.hh"
#include <iostream>

namespace fonts {
	std::map<std::string, sf::Font> assets;
	bool loaded = false;
	std::thread loadingThread;

	const std::string FONTS_META_FILE = "resource/meta/fonts.json";

	void performLoading() {
		std::ifstream inStream (fonts::FONTS_META_FILE, std::ifstream::in);
		nlohmann::json textureJson = nlohmann::json::parse(inStream);

		for (auto& textureDefinition : textureJson.items()) {
			std::string key = textureDefinition.key();
			nlohmann::json data = textureDefinition.value();
			std::string dataFile = data["file"];
			fonts::assets.emplace(key, sf::Font{});
			fonts::assets[key].loadFromFile(dataFile);
		}

		fonts::loaded = true;
	}

	void load() {
		fonts::loadingThread = std::thread(performLoading);
		fonts::loadingThread.detach();
	}

	void unload() {
		fonts::loaded = false;
		if (fonts::loadingThread.joinable()) {
			fonts::loadingThread.join();
		}
		fonts::assets.clear();
	}
}
