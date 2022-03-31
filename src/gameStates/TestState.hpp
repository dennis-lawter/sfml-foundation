#ifndef TESTSTATE_HPP_
#define TESTSTATE_HPP_
#include "generic/GameState.hpp"
#include "../gameObj/generic/GameObject.hpp"
#include "../tiled/World.hpp"
#include "../playerInput.hh"

class TestState : public GameState {
private:
	World world;
public:
	TestState(sf::RenderWindow& window);

	void processInput(sf::Event& event);
	void update();
	void draw();

	virtual ~TestState();
};

#endif
