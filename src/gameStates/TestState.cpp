#include "TestState.hpp"

TestState::TestState(sf::RenderWindow& window)
: GameState(window)
, world("intro", window) {
}

void TestState::processInput(sf::Event& event) {
	//playerInput::inputTopDown(event);
	playerInput::inputSideScroll(event);

	// ParticleObject test ({
	// 	{100, 100},
	// 	{0.f, -.1f},
	// 	{0.f, -.1f/120},
	// 	180,
	// 	sf::Color::White,
	// 	sf::Color::White
	// });
}

void TestState::update() {
	world.update();
}

void TestState::draw() {
	world.draw();
}

TestState::~TestState() {
}
