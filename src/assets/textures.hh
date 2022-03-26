#ifndef TEXTURES_HH_
#define TEXTURES_HH_
#include <thread>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "../extern/json.hpp"

namespace textures {
	extern std::map<std::string, sf::Texture> assets;
	extern bool loaded;
	extern std::thread loadingThread;

	void load();
	void unload();
}

#endif
