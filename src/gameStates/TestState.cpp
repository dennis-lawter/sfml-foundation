#include "TestState.hpp"

TestState::TestState()
: world("intro") {
}

void TestState::processInput(sf::Event& event) {
}

void TestState::update(sf::RenderWindow& window) {
	world.update();
}

void TestState::draw(sf::RenderWindow& window) {
	world.draw(window);
}

TestState::~TestState() {
}
