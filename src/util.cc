#include "util.hh"
#include <iostream>
#include <ctime>

namespace util {
	float lerp(float x0, float x1, float p) {
		p = std::clamp(p, 0.f, 1.f);
		return x0 + ((x1 - x0) * p);
	}

	sf::Vector2f tween(sf::Vector2f start, sf::Vector2f end, float p) {
		float x = lerp(start.x, end.x, p);
		float y = lerp(start.y, end.y, p);
		return sf::Vector2f(x, y);
	}

	void setRandomSeed() {
		srand(time(NULL));
	}

	void setSeed(unsigned int seed) {
		srand(seed);
	}

	int rangedRand(int min, int max) {
		if (max < min) {
			std::swap(max, min);
		}
		return rand() % ((max + 1) - min) + min;
	}

	float rangedRandFloat(float min, float max, int slices) {
		float random = rangedRand(0, slices);
		return lerp(min, max, random / slices);
	}

	sf::Color randomColor() {
		sf::Color c;
		c.r = rangedRand(0, 255);
		c.g = rangedRand(0, 255);
		c.b = rangedRand(0, 255);
		c.a = 255;
		return c;
	}

	sf::ConvexShape createConvexShape(std::vector<int> map) {
		sf::ConvexShape create;
		int largest = 0;
		create.setPointCount(map.size() / 2);
		for (unsigned int i = 0; i < (map.size() / 2); i++) {
			create.setPoint(0 + i, sf::Vector2f(map[0 + (i * 2)], map[1 + (i * 2)]));
			largest = (map[0 + (i * 2)] > largest) ? map[0 + (i * 2)] : largest;
			largest = (map[1 + (i * 2)] > largest) ? map[1 + (i * 2)] : largest;
		}
		create.setOrigin(sf::Vector2f((largest / 2.f), (largest / 2.f)));
		return create;
	}

	float InvSqrt(float x) {
		float xhalf = 0.5f * x;
		int i = *(int*)&x;            // store floating-point bits in integer
		i = 0x5f3759df - (i >> 1);    // initial guess for Newton's method
		x = *(float*)&i;              // convert new bits into float
		x = x * (1.5f - xhalf * x * x);     // One round of Newton's method
		return x;
	}
}
