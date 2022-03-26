#include "LoadingState.hpp"

LoadingState::LoadingState() {
	loadingRectangle.setFillColor(sf::Color(0xCC0066ff));
	loadingRectangle.setSize(sf::Vector2f(30.f, 30.f));
	loadingRectangle.setOrigin(sf::Vector2f(15.f, 15.f));
	loadingRectangle.setPosition(sf::Vector2f(defines::WIDTH - 30.f, defines::HEIGHT - 30.f));

	defenderSil.setPointCount(16);
	defenderSil.setPoint(0, sf::Vector2f(6, 1));
	defenderSil.setPoint(1, sf::Vector2f(2, 1));
	defenderSil.setPoint(2, sf::Vector2f(2, 2));
	defenderSil.setPoint(3, sf::Vector2f(1, 2));
	defenderSil.setPoint(4, sf::Vector2f(1, 7));
	defenderSil.setPoint(5, sf::Vector2f(2, 7));
	defenderSil.setPoint(6, sf::Vector2f(2, 6));
	defenderSil.setPoint(7, sf::Vector2f(3, 6));
	defenderSil.setPoint(8, sf::Vector2f(3, 7));
	defenderSil.setPoint(9, sf::Vector2f(5, 7));
	defenderSil.setPoint(10, sf::Vector2f(5, 6));
	defenderSil.setPoint(11, sf::Vector2f(6, 6));
	defenderSil.setPoint(12, sf::Vector2f(6, 7));
	defenderSil.setPoint(13, sf::Vector2f(7, 7));
	defenderSil.setPoint(14, sf::Vector2f(7, 2));
	defenderSil.setPoint(15, sf::Vector2f(6, 2));
	defenderSil.setFillColor(sf::Color(0xCC0066ff));
	defenderSil.setScale(sf::Vector2f(5.f, 5.f));
	defenderSil.setOrigin(sf::Vector2f(4.f,4.f));
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
	//loadingRectangle.rotate(1.f);
	defenderSil.rotate(1.f);
}

void LoadingState::draw(sf::RenderWindow& window) {
	//window.draw(loadingRectangle);
	window.draw(defenderSil);
}

LoadingState::~LoadingState() {
}
