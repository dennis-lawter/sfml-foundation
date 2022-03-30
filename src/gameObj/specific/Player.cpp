#include "Player.hpp"

Player::Player(std::string name)
: GameObject(name) {
}

void Player::move() {
	
	this->sprite.move(playerInput::getInputVector() * speed);
}

Player::~Player() {
}
