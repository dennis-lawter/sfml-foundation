#ifndef POWERUP_HPP_
#define POWERUP_HPP_
#include "GameObject.hpp"
#include "Player.hpp"
#include "Baddie.hpp"
#include "groups/BaddieGroup.hpp"
#include "groups/ParticleGroup.hpp"

class Powerup : public GameObject {
private:

	defines::PowerUp powerupSelect;
	Player* defender = nullptr;
	Baddie* baddie = nullptr;


	float speed = 0.8;

public:

	Powerup(defines::PowerUp powerupSelect, float ufoPosition, Player& defender);

	void oneUp(ParticleGroup& particleGroup);
	void coin(ParticleGroup& particleGroup);
	void coinOffScreen(ParticleGroup& particleGroup);
	void speedUp();
	void speedDown();
	void punch();
	void bomb();
	void agressive(Baddie& baddie);
	void passive(Baddie& baddie);
	void missile();

	void grantPowerUp(ParticleGroup& particleGroup);

	bool isOffScreen();
	void update(ParticleGroup& particleGroup);
};

#endif
