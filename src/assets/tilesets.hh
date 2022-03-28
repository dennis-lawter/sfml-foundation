#ifndef TILESETS_HH_
#define TILESETS_HH_
#include <thread>
#include <fstream>
#include "../extern/json.hpp"

namespace tilesets {
	extern std::map<std::string, std::string> assets;
	extern bool loaded;
	extern std::thread loadingThread;

	void load();
	void unload();
}

#endif
