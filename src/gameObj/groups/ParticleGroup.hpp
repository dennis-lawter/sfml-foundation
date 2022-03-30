#ifndef PARTICLEGROUP_HPP_
#define PARTICLEGROUP_HPP_
#include "../specific/Particle.hpp"

class ParticleGroup {
private:
	std::vector<ParticleObject> particleObjects;
	std::vector<ParticleText> particleTexts;
public:
	ParticleGroup();
	
	void createParticleObject(ParticleAttributeList particle);
	void createParticleText(std::string text, sf::Vector2f pos, sf::Color color);

	void update();
	void draw(sf::RenderWindow& window);	

	virtual ~ParticleGroup();
};

#endif
