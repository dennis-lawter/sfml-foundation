#include "Ufo.hpp"

Ufo::Ufo()
	: GameObject(resources::textures["ufo"], 0, 8) {
	ufoSpawnSound.setBuffer(resources::soundFile["ufoFire"]);
	ufoSpawnSound.play();
	this->sprite.setTextureRect(IntRect(0, 0, 16, 8));
	if (util::rangedRand(0, 1) % 2 == 0) {
		this->sprite.setPosition(defines::WIDTH, 8);
		isMovingLeft = true;
	} else {
		this->sprite.setPosition(-this->getWidth(), 8);
		isMovingLeft = false;
	}
	ufoFireRandom = util::rangedRand(defines::UFO_FIRE_START, defines::UFO_FIRE_END);
}

void Ufo::move() {
	if (isMovingLeft) {
		this->sprite.move(-speed, 0);
	} else {
		this->sprite.move(speed, 0);
	}
}

bool Ufo::isOffScreen() {
	return (this->getX() < -this->getWidth() - 1 || this->getX() > defines::WIDTH + 1);
}

void Ufo::ufoFire() {
	if (hasFired) {
		return;
	}
	if (this->getX() + this->getWidth() / 2 < ufoFireRandom && isMovingLeft) {
		hasFired = true;
		return;
	} else if (this->getX() + this->getWidth() / 2 > ufoFireRandom && !isMovingLeft) {
		hasFired = true;
		return;
	}
}

void Ufo::update() {
	move();
	ufoFire();
	if (animationSwap && animationBuffer > animationTimer) {
		this->sprite.setTextureRect(IntRect(16, 0, 16, 8));
		animationSwap = !animationSwap;
		animationBuffer = 0;
	} else if (!animationSwap && animationBuffer > animationTimer) {
		this->sprite.setTextureRect(IntRect(0, 0, 16, 8));
		animationSwap = !animationSwap;
		animationBuffer = 0;
	}
	animationBuffer += util::rangedRand(1, 2);
}
