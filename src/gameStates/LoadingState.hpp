#ifndef LOADINGSTATE_HPP_
#define LOADINGSTATE_HPP_
#include "generic/GameState.hpp"
#include "../util.hh"
#include "../assets/textures.hh"
#include "../assets/sounds.hh"
#include "../assets/fonts.hh"

class LoadingState : public GameState {
private:
	sf::RectangleShape loadingRectangle;
	sf::ConvexShape defenderSil;
public:
	LoadingState();

	void processInput(sf::Event& event);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	virtual ~LoadingState();
};

#endif
