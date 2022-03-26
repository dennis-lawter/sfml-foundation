#include "LoadingState.hpp"

LoadingState::LoadingState() {
	this->defenderSil = util::createConvexShape({5,0,1,0,1,1,0,1,0,6,1,6,1,5,2,5,2,6,4,6,4,5,5,5,5,6,6,6,6,1,5,1});
	this->defenderSil.setFillColor(sf::Color(0xCC0066ff));
	this->defenderSil.setScale(sf::Vector2f(5.f, 5.f));
	this->defenderSil.setPosition(sf::Vector2f(defines::WIDTH - 30.f, defines::HEIGHT - 30.f));

	// initiate loading threads
	textures::load();
	sounds::load();
	fonts::load();
}

void LoadingState::processInput(sf::Event& event) {
}

void LoadingState::update(sf::RenderWindow& window) {
	if (this->timer >= this->LOAD_MIN) {
		if (
			textures::loaded &&
			sounds::loaded &&
			fonts::loaded
		) {
			return;
		}
	}
	
	this->defenderSil.rotate(1.f);
	this->timer++;
}

void LoadingState::draw(sf::RenderWindow& window) {
	window.draw(this->defenderSil);
}

LoadingState::~LoadingState() {
}
