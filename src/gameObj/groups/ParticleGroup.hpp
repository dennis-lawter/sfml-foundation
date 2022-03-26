#ifndef PARTICLEGROUP_HPP_
#define PARTICLEGROUP_HPP_
#include "../Particle.hpp"

class ParticleGroup {
private:
	std::vector<ParticleObject> particleObjects;
	std::vector<ParticleText> particleTexts;
public:
	void createParticleObject(ParticleAttributeList particle);
	void createParticleText(std::string text, sf::Vector2f pos, sf::Color color);

	void update();
	void draw(RenderWindow& window);	
};

#endif
