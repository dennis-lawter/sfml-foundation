#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_
#include "generic/GameObject.hpp"

struct ParticleAttributeList {
	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;
	int timeToLive;
	Color initialColor;
	Color finalColor;
	float initScaleFactor = 1.f;
	float initRotationFactor = 0.f;
};

class Particle : public ParticleAttributeList {
protected:
	int age = 0;
	float agePercentage = 0.f;

	void move();
	Color currentColor();
public:
	bool isReadyToDie = false;
	Particle(ParticleAttributeList attributes);

	void update();
};

class ParticleText : public Particle {
private:
	Text text;
public:
	ParticleText(ParticleAttributeList attributes, string text);

	void update();
	void draw(RenderWindow& window);
};

class ParticleObject : public GameObject, public Particle {
public:
	ParticleObject(ParticleAttributeList attributes);

	void update();
};

#endif
