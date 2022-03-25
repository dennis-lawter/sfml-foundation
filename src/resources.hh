#ifndef RESOURCES_HH_
#define RESOURCES_HH_

#include <map>
#include <exception>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "defines.hh"

using namespace sf;
using namespace std;

namespace resources {
	extern map<string, Texture> textures;
	extern map<string, SoundBuffer> soundFile;
	extern Font font;
	extern string highScoresFileName;

	void loadResources();
}

#endif
