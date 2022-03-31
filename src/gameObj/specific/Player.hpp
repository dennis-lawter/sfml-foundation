#ifndef PLAYER_HH_
#define PLAYER_HH_
#include "../generic/GameObject.hpp"
#include "../groups/ParticleGroup.hh"
#include "../../playerInput.hh"
#include <iostream>

class Player : public GameObject {
private:
	float speed = 1.9f;
	float sideSpeed = 0.5f;

	const float MAX_VELOCITY = 3.f;
	float jumpHeight = 20.f;
public:
	bool canJump = true;
	sf::Vector2f velocity;

	Player(std::string);
	sf::FloatRect getHitBox();
	void update();
	virtual ~Player();

};

#endif
