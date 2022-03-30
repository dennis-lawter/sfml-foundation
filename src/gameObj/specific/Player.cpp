#include "Player.hpp"

Player::Player(std::string name)
: GameObject(name) {
}

void Player::update() {
	sf::Vector2f test = playerInput::getInputVector();
	this->sprite.move( test* speed);
	// std::cout << test.x << "   "<< test.y << std::endl;
	GameObject::update();
}

Player::~Player() {
}
