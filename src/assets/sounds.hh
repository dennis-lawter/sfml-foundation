#ifndef SOUNDS_HH_
#define SOUNDS_HH_
#include <thread>
#include <fstream>
#include <SFML/Audio.hpp>
#include "../extern/json.hpp"

namespace sounds {
	extern std::map<std::string, sf::SoundBuffer> assets;
	extern bool loaded;
	extern std::thread loadingThread;

	void load();
	void unload();
}

#endif
