#include "Baddie.hpp"

Baddie::Baddie(Texture& texture, int x, int y)
	: GameObject(texture, x, y) {
	this->sprite.setOrigin(4.f, 4.f);
	this->sprite.setTextureRect(IntRect(0, 0, 8, 8));
	int quadrant = util::rangedRand(0, 3);
	switch (quadrant) {
	case 0:
	case 1:
		this->startingPosition.x = util::rangedRand(-32, defines::WIDTH + 32);
		this->startingPosition.y = -32;
		break;
	case 2:
		this->startingPosition.x = defines::WIDTH + 32;
		this->startingPosition.y = util::rangedRand(-32, defines::HEIGHT / 2);
		break;
	case 3:
		this->startingPosition.x = -32;
		this->startingPosition.y = util::rangedRand(-32, defines::HEIGHT / 2);
		break;
	}
	this->setPosition(this->startingPosition);
	animationFinishTime = util::rangedRand(380 / 2, 380);
	animationPlayerDead = util::rangedRand(200 / 2, 200);
}

void Baddie::moveRight() {
	this->sprite.move(speed, 0);
}

void Baddie::moveLeft() {
	this->sprite.move(-(speed), 0);
}

void Baddie::moveDown() {
	this->sprite.move(0, ADVANCE_DISTANCE);
}

void Baddie::kamikaze() {
	if (gettingAngry < 180 && isUpright) {
		this->sprite.setRotation(gettingAngryShakes);
		gettingAngryShakes = -gettingAngryShakes;
		this->sprite.scale(1.003f, 1.003f);
		gettingAngry++;
		isUpright = false;
	} else if (gettingAngry < 180 && !isUpright) {
		this->sprite.setRotation(0.f);
		this->sprite.scale(1.003f, 1.003f);
		gettingAngry++;
		isUpright = true;
	} else if (!eesComing && gettingAngry >= 180) {
		eesComing = true;
	} else {
		this->sprite.move(0, 2);
	}
}

void Baddie::jumpAnimate() {
	if (beforeWinPosition == Vector2f(0.f, 0.f)) {
		beforeWinPosition = this->getPosition();
	}
	if (jump) {
		this->sprite.move(0,-15);
		jump = false;
	} else if (!jump) {
		this->setPosition(beforeWinPosition);
		jump = true;
	}
}

void Baddie::draw(RenderWindow& window) {
	if (!ohHeMad && util::rangedRand(0, 20) == 0) {
		this->sprite.setRotation(util::rangedRandFloat(-10.0, 10.0, 200));
	} else if (!ohHeMad) {
		this->sprite.setRotation(0.f);
	}
	if (animationSwap && animationBuffer > animationTimer) {
		this->sprite.setTextureRect(IntRect(8, 0, 8, 8));
		animationSwap = !animationSwap;
		animationBuffer = 0;
	} else if (!animationSwap && animationBuffer > animationTimer) {
		this->sprite.setTextureRect(IntRect(0, 0, 8, 8));
		animationSwap = !animationSwap;
		animationBuffer = 0;
	}
	animationBuffer += util::rangedRand(1, 2);
	GameObject::draw(window);
}

void Baddie::update() {
	if (util::rangedRand(0, KAMI_RANDOM) == 0) {
		ohHeMad = true;
		
	}
	if (ohHeMad) {
		kamikaze();
	}
}
