#include "BaddieBullet.hpp"

BaddieBullet::BaddieBullet(float x, float y)
	: GameObject(resources::textures["bullet"], x, y) {

}

bool BaddieBullet::isOffScreen() {
	return (this->getY() >= 128);
}

void BaddieBullet::update() {
	this->sprite.move(0, speed);
}
