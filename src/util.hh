#ifndef UTIL_HH_
#define UTIL_HH_

#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace util {
	float lerp(float x0, float x1, float p);
	sf::Vector2f tween(sf::Vector2f start, sf::Vector2f end, float p);

	void setRandomSeed();
	void setSeed(unsigned int seed);
	int rangedRand(int min, int max);
	float rangedRandFloat(float min, float max,int slices);
	sf::Color randomColor();
	sf::ConvexShape createConvexShape(std::vector<int> map);
}

#endif
