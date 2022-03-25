#include "Powerup.hpp"

Powerup::Powerup(defines::PowerUp powerupSelect, float ufoPosition, Player& defender)
	: GameObject(resources::textures[defines::POWER_UP_LIST[powerupSelect]], ufoPosition, 16) {
	sprite.setColor(Color(0xFFFFFFBB));
	this->powerupSelect = powerupSelect;
	this->defender = &defender;
	this->sprite.setOrigin(4, 4);
}

void Powerup::oneUp(ParticleGroup& particleGroup) {
	if (score::currentLives < defines::LIVES_CAP) {
		score::currentLives++;
	} else {
		score::score += 1000;
		particleGroup.createParticleText("+1000", getPosition(), Color::Cyan);
	}
}

void Powerup::coin(ParticleGroup& particleGroup) {
	score::score += 1000;
	particleGroup.createParticleText("+1000", getPosition(), Color::Cyan);
}

void Powerup::coinOffScreen(ParticleGroup& particleGroup) {
	if (score::score == 0) return;
	int scoreChange = -1000;

	if (score::score < 1000) {
		scoreChange = -score::score;
	}

	score::score += scoreChange;
	
	Vector2f position = getPosition();
	position.y -= 8.f;
	particleGroup.createParticleText(to_string(scoreChange), position, Color::Red);
}

void Powerup::speedUp() {
	defender->speed *= 1.2;
}

void Powerup::speedDown() {
	defender->speed *= 0.8;
}

void Powerup::punch() {
	defender->isPunch = true;
}

void Powerup::bomb() {
	if (!defender->isInvuln) {
		score::currentLives--;
		defender->isInvuln = true;
	}
}

void Powerup::agressive(Baddie& baddie) {
	baddie.speed *= 1.2;
}

void Powerup::passive(Baddie& baddie) {
	baddie.speed *= 0.8;
}

void Powerup::missile() {
	if (defender->bulletSpeedModifier >= defines::BULLET_SPEED_MODIFIER_CAP) {
		return;
	}
	defender->bulletSpeedModifier += 0.2;
}


bool Powerup::isOffScreen() {
	return (this->getY() > defines::HEIGHT);
}

void Powerup::grantPowerUp(ParticleGroup& particleGroup) {
	switch (powerupSelect) {
	case defines::PowerUp::OneUp:
		oneUp(particleGroup);
		break;
	case defines::PowerUp::Coin:
		coin(particleGroup);
		break;
	case defines::PowerUp::SpeedUp:
		speedUp();
		break;
	case defines::PowerUp::SpeedDown:
		speedDown();
		break;
	case defines::PowerUp::Punch:
		punch();
		break;
	case defines::PowerUp::Bomb:
		bomb();
		break;
	case defines::PowerUp::Missile:
		missile();
		break;
	case defines::PowerUp::Curved:
		defender->isBulletCurved = true;
		break;
	default:
		break;
	}
}

void Powerup::update(ParticleGroup& particleGroup) {
	this->sprite.move(0, speed);
	if (powerupSelect == defines::Bomb) {
		this->sprite.scale({1.005f, 1.005f});
	} else if (powerupSelect == defines::Coin && isOffScreen()) {
		coinOffScreen(particleGroup);
	}
}
