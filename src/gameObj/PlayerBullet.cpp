#include "PlayerBullet.hpp"

PlayerBullet::PlayerBullet(float x, float speed)
	: GameObject(resources::textures["bullet"], x, 112) {
	this->speed = speed;
}

bool PlayerBullet::isOffScreen() {
	return (this->getY() <= 8);
}

void PlayerBullet::update() {
	this->sprite.move(shift, -speed);
}
