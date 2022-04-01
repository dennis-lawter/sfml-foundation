#include "Player.hpp"

Player::Player(std::string name)
	: GameObject(name) {
}

void Player::update() {
	sf::Vector2f test = playerInput::getInputVector();
	this->oldPosition = this->sprite.getPosition();
	//this->sprite.move(test * speed);

	velocity.x = 0.0f;

	if (velocity.y > 0.02f) {
		canJump = false;
	}
	
	if (playerInput::getInputVector().x >= 1.f) {
		velocity.x += speed;
	}
	if (playerInput::getInputVector().x <= -1.f) {
		velocity.x -= speed;
	}
	if (playerInput::getInputVector().y <= -1.f && canJump) {
		canJump = false;

		velocity.y = -(1/util::InvSqrt(4.0f * defines::GRAVITY * jumpHeight));
	}

	velocity.y += defines::GRAVITY;

	this->sprite.move(velocity);


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
