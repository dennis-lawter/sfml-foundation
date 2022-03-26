#include "ParticleGroup.hpp"

void ParticleGroup::createParticleObject(ParticleAttributeList attributes) {
	particleObjects.emplace_back(attributes);
}

void ParticleGroup::createParticleText(std::string text, sf::Vector2f pos, sf::Color color) {
	Color finalColor = color;
	finalColor.a = 0;
	ParticleAttributeList attributes {
		pos,
		{0.f, -.1f},
		{0.f, -.1f/120},
		60,
		color,
		finalColor
	};
	particleTexts.emplace_back(attributes, text);
}

void ParticleGroup::update() {
	for (auto& particle : particleObjects) {
		particle.update();
	}
	for (auto& particle : particleTexts) {
		particle.update();
	}

	for (auto iter = particleObjects.begin(); iter != particleObjects.end(); iter++) {
		if (iter->isReadyToDie) {
			particleObjects.erase(iter--);
			continue;
		}
	}
	for (auto iter = particleTexts.begin(); iter != particleTexts.end(); iter++) {
		if (iter->isReadyToDie) {
			particleTexts.erase(iter--);
			continue;
		}
	}
}

void ParticleGroup::draw(RenderWindow& window) {
	for (auto& particle : particleObjects) {
		particle.draw(window);
	}
	for (auto& particle : particleTexts) {
		particle.draw(window);
	}
}
