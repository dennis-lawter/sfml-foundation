#ifndef WORLDS_HH_
#define WORLDS_HH_
#include <thread>
#include <fstream>
#include "../extern/json.hpp"

namespace worlds {
	extern std::map<std::string, std::string> assets;
	extern bool loaded;
	extern std::thread loadingThread;

	void load();
	void unload();
}

#endif
