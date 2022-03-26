#ifndef SPLASHLOGOSTATE_HPP_
#define SPLASHLOGOSTATE_HPP_

#include "generic/GameState.hpp"
#include "../rendering/GameText.hpp"

class SplashLogoState : public GameState {
private:
	sf::Sprite logo;
	GameText bitonic;
	GameText us;

public:
	SplashLogoState();

	void processInput(sf::Event& event);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	virtual ~SplashLogoState();

};

#endif
