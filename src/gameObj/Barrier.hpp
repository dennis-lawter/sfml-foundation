#ifndef BARRIER_HPP_
#define BARRIER_HPP_
#include "GameObject.hpp"

class Barrier : public GameObject {
public:
	Vector2f startingPosition;
	Vector2f destination;
	Barrier(int x, int y);
};

#endif
