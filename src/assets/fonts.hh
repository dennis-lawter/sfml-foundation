#ifndef FONTS_HH_
#define FONTS_HH_
#include <thread>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "../extern/json.hpp"

namespace fonts {
	extern std::map<std::string, sf::Font> assets;
	extern bool loaded;
	extern std::thread loadingThread;

	void load();
	void unload();
}

#endif
