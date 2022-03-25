#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_
#include <SFML/Graphics.hpp>
#include "../defines.hh"

class GameState {
public:
	enum State {
		Loading
	};

	bool isEnding = false;

	virtual void processInput(sf::Event& event) = 0;
	virtual void update(sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	virtual ~GameState() {}
};

#endif
