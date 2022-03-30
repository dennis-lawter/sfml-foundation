#ifndef PLAYER_HH_
#define PLAYER_HH_
#include "../generic/GameObject.hpp"
#include "../../playerInput.hh"

class Player : public GameObject {
private:
	float speed = 5.f;
public:
	Player(std::string);
	void move();
	virtual ~Player();
};

#endif
