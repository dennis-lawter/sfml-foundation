#include "LoadingState.hpp"

LoadingState::LoadingState() {
	defenderSil = util::createConvexShape({5,0,1,0,1,1,0,1,0,6,1,6,1,5,2,5,2,6,4,6,4,5,5,5,5,6,6,6,6,1,5,1});
	defenderSil.setFillColor(sf::Color(0xCC0066ff));
	defenderSil.setScale(sf::Vector2f(5.f, 5.f));
	defenderSil.setPosition(sf::Vector2f(defines::WIDTH - 30.f, defines::HEIGHT - 30.f));



	// initiate loading threads
	textures::load();
}

void LoadingState::processInput(sf::Event& event) {
}

void LoadingState::update(sf::RenderWindow& window) {
	// if (textures::loaded) {
	// 	return;
	// }
	defenderSil.rotate(1.f);
}

void LoadingState::draw(sf::RenderWindow& window) {
	window.draw(defenderSil);
}

LoadingState::~LoadingState() {
}
