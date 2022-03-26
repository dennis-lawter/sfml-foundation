#ifndef ANIMATIONS_HH_
#define ANIMATIONS_HH_
#include <thread>
#include <fstream>
#include "../extern/json.hpp"
#include "../rendering/AnimationList.hpp"

namespace animations {
	extern std::map<std::string, AnimationList> assets;
	extern bool loaded;
	extern std::thread loadingThread;

	void load();
	void unload();
}

#endif
