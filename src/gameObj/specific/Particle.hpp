#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_
#include "../generic/GameObject.hpp"

struct ParticleAttributeList {
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	int timeToLive;
	sf::Color initialColor;
	sf::Color finalColor;
	float initScaleFactor = 1.f;
	float initRotationFactor = 0.f;
};

class Particle : public ParticleAttributeList {
protected:
	int age = 0;
	float agePercentage = 0.f;

	void move();
	sf::Color currentColor();
public:
	bool isReadyToDie = false;

	Particle(ParticleAttributeList attributes);

	void update();

	virtual ~Particle();
};

class ParticleText : public Particle {
private:
	sf::Text text;
public:
	ParticleText(ParticleAttributeList attributes, std::string text);

	void update();
	void draw(sf::RenderWindow& window);

	virtual ~ParticleText();
};

class ParticleObject : public GameObject, public Particle {
private:
	std::string PARTICLE_NAME = "particle";
public:
	ParticleObject(ParticleAttributeList attributes);

	void update();

	virtual ~ParticleObject();
};

#endif
