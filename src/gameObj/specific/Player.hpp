#ifndef PLAYER_HH_
#define PLAYER_HH_
#include "../generic/GameObject.hpp"
#include "../groups/ParticleGroup.hh"
#include "../../playerInput.hh"
#include <iostream>

class Player : public GameObject {
private:
	float speed = 1.9f;
public:
	Player(std::string);
	sf::FloatRect getHitBox();
	void update();
	virtual ~Player();
};

#endif
