#include "Player.hpp"

Player::Player(std::string name)
	: GameObject(name) {
}

void Player::update() {
	sf::Vector2f test = playerInput::getInputVector();
	this->oldPosition = this->sprite.getPosition();
	this->sprite.move(test * speed);
	GameObject::update();
}

sf::FloatRect Player::getHitBox() {
	sf::FloatRect rect = GameObject::getHitBox();
	rect.top += 1.f;
	rect.left += 1.f;
	rect.width -= 2.f;
	rect.height -= 2.f;
	return rect;
}

Player::~Player() {
}
