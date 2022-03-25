#ifndef BADDIEBULLET_HPP_
#define BADDIEBULLET_HPP_
#include "GameObject.hpp"

class BaddieBullet : public GameObject {
public:
	float speed = 1;

	BaddieBullet(float x, float y);

	bool isOffScreen();
	void update();
};

#endif
