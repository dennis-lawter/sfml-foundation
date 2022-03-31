#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../defines.hh"
#include "../../assets/assets.hh"
#include "../../util.hh"

class GameState {
public:
	enum State {
		SplashLogo,
		Loading,
		Test
	};

	bool isEnding = false;
	sf::RenderWindow& window;

	GameState(sf::RenderWindow& window)
	:window(window) {};

	virtual void processInput(sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	virtual ~GameState() {}
};

#endif
