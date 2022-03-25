#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_
#include <SFML/Graphics.hpp>
#include "../GameText.hpp"
#include "../resources.hh"
#include "../score.hh"
#include "../util.hh"
using namespace sf;

class GameState {
public:
	enum State {
		Title,
		GamePlay,
		GameOver,
		Attract,
		ShowScore,
		EnterInitials
	};

	bool isEnding = false;

	virtual void processInput(Event& event) = 0;
	virtual void update(RenderWindow& window) = 0;
	virtual void draw(RenderWindow& window) = 0;

	virtual ~GameState() {}
};

#endif
