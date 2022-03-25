#ifndef PARTICLEGROUP_HPP_
#define PARTICLEGROUP_HPP_
#include "../Particle.hpp"

class ParticleGroup {
private:
	vector<ParticleObject> particleObjects;
	vector<ParticleText> particleTexts;
public:
	void createParticleObject(ParticleAttributeList particle);
	void createParticleText(string text, Vector2f pos, Color color);

	void update();
	void draw(RenderWindow& window);	
};

#endif
