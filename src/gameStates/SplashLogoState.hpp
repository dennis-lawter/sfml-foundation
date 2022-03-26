#ifndef SPLASHLOGOSTATE_HPP_
#define SPLASHLOGOSTATE_HPP_

#include "generic/GameState.hpp"
#include "../assets/assets.hh"

class SplashLogoState : public GameState {
private:

public:
	SplashLogoState();

	void processInput(sf::Event& event);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	virtual ~SplashLogoState();

};

#endif
