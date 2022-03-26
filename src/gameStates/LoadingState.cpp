#include "LoadingState.hpp"

LoadingState::LoadingState() {
	loadingRectangle.setFillColor(sf::Color(0xCC0066ff));
	loadingRectangle.setSize(sf::Vector2f(30.f, 30.f));
	loadingRectangle.setOrigin(sf::Vector2f(15.f, 15.f));
	loadingRectangle.setPosition(sf::Vector2f(defines::WIDTH-30.f, defines::HEIGHT-30.f));

	// initiate loading threads
	textures::load();
	sounds::load();
	fonts::load();
}

void LoadingState::processInput(sf::Event& event) {
}

void LoadingState::update(sf::RenderWindow& window) {
	if (textures::loaded) {
		return;
	}
	loadingRectangle.rotate(1.f);
}

void LoadingState::draw(sf::RenderWindow& window) {
	window.draw(loadingRectangle);
}

LoadingState::~LoadingState() {
}
