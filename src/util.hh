#ifndef UTIL_HH_
#define UTIL_HH_

#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

namespace util {
	float lerp(float x0, float x1, float p);
	Vector2f tween(Vector2f start, Vector2f end, float p);

	void setRandomSeed();
	void setSeed(unsigned int seed);
	int rangedRand(int min, int max);
	float rangedRandFloat(float min, float max,int slices);
	Color randomColor();
}

#endif
