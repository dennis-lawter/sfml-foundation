#ifndef TESTSTATE_HPP_
#define TESTSTATE_HPP_
#include "generic/GameState.hpp"
#include "../gameObj/generic/GameObject.hpp"
#include "../tiled/World.hpp"

class TestState : public GameState {
private:
	GameObject obj;

	World world;
public:
	TestState();

	void processInput(sf::Event& event);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	virtual ~TestState();
};

#endif
