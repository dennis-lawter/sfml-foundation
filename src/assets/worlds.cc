#include "worlds.hh"
#include <iostream>

namespace worlds {
	std::map<std::string, std::string> assets;
	bool loaded = false;
	std::thread loadingThread;

	const std::string WORLDS_META_FILE = "resource/meta/worlds.json";

	void performLoading() {
		std::ifstream inStream (worlds::WORLDS_META_FILE, std::ifstream::in);
		nlohmann::json textureJson = nlohmann::json::parse(inStream);

		for (auto& textureDefinition : textureJson.items()) {
			std::string key = textureDefinition.key();
			nlohmann::json data = textureDefinition.value();
			std::string dataFile = data["file"];
			worlds::assets[key] = dataFile;
		}

		worlds::loaded = true;
	}

	void load() {
		worlds::loadingThread = std::thread(performLoading);
		worlds::loadingThread.detach();
	}

	void unload() {
		worlds::loaded = false;
		if (worlds::loadingThread.joinable()) {
			worlds::loadingThread.join();
		}
		worlds::assets.clear();
	}
}
