#include "animations.hh"
#include <iostream>

namespace animations {
	std::map<std::string, std::string> assets;
	bool loaded = false;
	std::thread loadingThread;

	const std::string ANIMATIONS_META_FILE = "resource/meta/animations.json";

	void performLoading() {
		std::ifstream inStream (animations::ANIMATIONS_META_FILE, std::ifstream::in);
		nlohmann::json jsonData = nlohmann::json::parse(inStream);

		for (auto& textureDefinition : jsonData.items()) {
			std::string key = textureDefinition.key();
			nlohmann::json data = textureDefinition.value();
			// std::string dataFile = data["file"];
			// animations::assets[key] = dataFile;
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
