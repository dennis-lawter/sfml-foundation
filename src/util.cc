#include "util.hh"
#include <iostream>
#include <ctime>

namespace util {
	float lerp(float x0, float x1, float p) {
		p = clamp(p, 0.f, 1.f);
		return x0 + ((x1 - x0) * p);
	}

	Vector2f tween(Vector2f start, Vector2f end, float p) {
		float x = lerp(start.x, end.x, p);
		float y = lerp(start.y, end.y, p);
		return Vector2f(x, y);
	}

	void setRandomSeed() {
		srand (time(NULL));
	}

	void setSeed(unsigned int seed) {
		srand(seed);
	}

	int rangedRand(int min, int max) {
		if (max < min) {
			swap(max, min);
		}
		return rand() % ((max + 1) - min) + min;
	}

	float rangedRandFloat(float min, float max, int slices) {
		float random = rangedRand(0, slices);
		return lerp(min, max, random / slices);
	}

	Color randomColor() {
		Color c;
		c.r = rangedRand(0, 255);
		c.g = rangedRand(0, 255);
		c.b = rangedRand(0, 255);
		c.a = 255;
		return c;
	}
}
