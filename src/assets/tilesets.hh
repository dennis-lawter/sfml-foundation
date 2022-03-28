#ifndef TILESETS_HH_
#define TILESETS_HH_
#include <thread>
#include <fstream>
#include "../extern/json.hpp"
#include "../rendering/TileSet.hpp"

namespace tilesets {
	extern std::map<std::string, TileSet> assets;
	extern bool loaded;
	extern std::thread loadingThread;

	void load();
	void unload();
}

#endif
