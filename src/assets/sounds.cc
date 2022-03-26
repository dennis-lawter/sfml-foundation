#include "sounds.hh"
#include <iostream>
#include <chrono>

namespace sounds {
	std::map<std::string, sf::SoundBuffer> assets;
	bool loaded = false;
	std::thread loadingThread;

	const std::string SOUNDS_META_FILE = "resource/meta/sounds.json";

	void performLoading() {
		std::ifstream inStream (sounds::SOUNDS_META_FILE, std::ifstream::in);
		nlohmann::json textureJson = nlohmann::json::parse(inStream);

		for (auto& textureDefinition : textureJson.items()) {
			std::string key = textureDefinition.key();
			nlohmann::json data = textureDefinition.value();
			std::string dataFile = data["file"];
			sounds::assets.emplace(key, sf::SoundBuffer{});
			sounds::assets[key].loadFromFile(dataFile);
		}

		sounds::loaded = true;
	}

	void load() {
		sounds::loadingThread = std::thread(performLoading);
		sounds::loadingThread.detach();
	}

	void unload() {
		sounds::loaded = false;
		if (sounds::loadingThread.joinable()) {
			sounds::loadingThread.join();
		}
		sounds::assets.clear();
	}
}
