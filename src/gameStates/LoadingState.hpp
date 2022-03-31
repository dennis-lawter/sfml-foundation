#ifndef LOADINGSTATE_HPP_
#define LOADINGSTATE_HPP_
#include "generic/GameState.hpp"
#include "../util.hh"
#include "../assets/assets.hh"

class LoadingState : public GameState {
private:
	const int LOAD_MIN = 60;
	sf::RectangleShape loadingRectangle;
	sf::ConvexShape defenderSil;
	int timer = 0;
public:
	LoadingState(sf::RenderWindow& window);

	void processInput(sf::Event& event);
	void update();
	void draw();

	virtual ~LoadingState();
};

#endif
