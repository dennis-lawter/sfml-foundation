#include "Player.hpp"

Player::Player(std::string name)
	: GameObject(name) {
}

void Player::update() {
	// particleGroup::createParticleObject({
	// 	this->getPosition(),
	// 	{util::rangedRandFloat(-1.f, 1.f, 100), util::rangedRandFloat(-1.f, 1.f, 100)},
	// 	{util::rangedRandFloat(-.1f, .1f, 100), util::rangedRandFloat(-.1f, .1f, 100)},
	// 	60,
	// 	util::randomColor(),
	// 	util::randomColor()
	// });
	particleGroup::createParticleText(
		"Howdy ho",
		this->getPosition(),
		sf::Color::Magenta
	);
	sf::Vector2f test = playerInput::getInputVector();
	this->oldPosition = this->sprite.getPosition();
	this->sprite.move(test * speed);
	// std::cout << test.x << "   "<< test.y << std::endl;
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
