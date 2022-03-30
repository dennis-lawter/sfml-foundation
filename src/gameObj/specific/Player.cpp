#include "Player.hpp"

Player::Player(std::string name)
	: GameObject(name) {
}

void Player::update() {
	particleGroup::createParticleObject({
		this->getPosition(),
		{util::rangedRandFloat(-1.f, 1.f, 100), util::rangedRandFloat(-1.f, 1.f, 100)},
		{util::rangedRandFloat(-.1f, .1f, 100), util::rangedRandFloat(-.1f, .1f, 100)},
		60,
		util::randomColor(),
		util::randomColor()
	});
	sf::Vector2f test = playerInput::getInputVector();
	this->sprite.move(test * speed);
	// std::cout << test.x << "   "<< test.y << std::endl;
	GameObject::update();
}

Player::~Player() {
}
