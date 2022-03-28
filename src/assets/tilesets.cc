#include "tilesets.hh"

namespace tilesets {
	std::map<std::string, TileSet> assets;
	bool loaded = false;
	std::thread loadingThread;

	const std::string META_FILE = "resource/meta/tilesets.json";

	void performLoading() {
		std::ifstream inStream (tilesets::META_FILE, std::ifstream::in);
		nlohmann::json jsonData = nlohmann::json::parse(inStream);

		for (auto& definition : jsonData.items()) {
			std::string key = definition.key();
			nlohmann::json data = definition.value();
			tilesets::assets.emplace(key, TileSet{});
			tilesets::assets[key].width = data["width"];
			tilesets::assets[key].height = data["height"];
			tilesets::assets[key].tilesWide = data["tilesWide"];
			tilesets::assets[key].tilesTall = data["tilesTall"];
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
