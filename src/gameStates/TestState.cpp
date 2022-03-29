#include "TestState.hpp"

TestState::TestState()
: obj("player")
, world("intro") {
}

void TestState::processInput(sf::Event& event) {
}

void TestState::update(sf::RenderWindow& window) {
	obj.update();
}

void TestState::draw(sf::RenderWindow& window) {
	obj.draw(window);
	world.draw(window);
}

TestState::~TestState() {
}
