#include "TestState.hpp"

TestState::TestState()
: world("intro") {
}

void TestState::processInput(sf::Event& event) {
	playerInput::inputTopDown(event);
	// playerInput::inputSideScroll(event);

	// ParticleObject test ({
	// 	{100, 100},
	// 	{0.f, -.1f},
	// 	{0.f, -.1f/120},
	// 	180,
	// 	sf::Color::White,
	// 	sf::Color::White
	// });
}

void TestState::update(sf::RenderWindow& window) {
	world.update();
}

void TestState::draw(sf::RenderWindow& window) {
	world.draw(window);
}

TestState::~TestState() {
}
