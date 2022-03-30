#ifndef PARTICLEGROUP_HH_
#define PARTICLEGROUP_HH_
#include "../specific/Particle.hpp"
#include "../../util.hh"
#include <vector>

namespace particleGroup {
	void createParticleObject(ParticleAttributeList particle);
	void createParticleText(std::string text, sf::Vector2f pos, sf::Color color);

	void update();
	void draw();
	void setWindow(sf::RenderWindow& window);
};

#endif
