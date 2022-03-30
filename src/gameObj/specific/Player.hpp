#ifndef PLAYER_HH_
#define PLAYER_HH_
#include "../generic/GameObject.hpp"
#include "../../playerInput.hh"
#include <iostream>

class Player : public GameObject {
private:
	float speed = 5.f;
public:
	Player(std::string);
	void update();
	virtual ~Player();
};

#endif
