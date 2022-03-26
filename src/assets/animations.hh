#ifndef ANIMATIONS_HH_
#define ANIMATIONS_HH_
#include <thread>
#include <fstream>
#include "../extern/json.hpp"

namespace animations {
	extern std::map<std::string, std::string> assets;
	extern bool loaded;
	extern std::thread loadingThread;

	void load();
	void unload();
}

#endif
