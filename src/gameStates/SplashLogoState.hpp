#ifndef SPLASHLOGOSTATE_HPP_
#define SPLASHLOGOSTATE_HPP_

#include "generic/GameState.hpp"
#include "../rendering/GameText.hpp"

class SplashLogoState : public GameState {
private:

	sf::Color initialColor;
	sf::Color finalColor;
	sf::Color currentColor;
	sf::Sprite logo;
	GameText bitonic;
	GameText us;

	sf::Vector2f initialScale;
	sf::Vector2f curretScale;
	const sf::Vector2f WIDE_SCALE = {6.f, 3.f};
	const sf::Vector2f HEIGHT_SCARE = {3.f, 6.f};

	int timer = 0;
	const int FADE_IN_MAX = 30;
	const int STRETCH_WIDE_START = 30;
	const int STRETCH_WIDE_END = 40;
	const int STRETCH_TALL = 150;
	const int STATE_END = 180;

public:
	SplashLogoState();

	void processInput(sf::Event& event);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	virtual ~SplashLogoState();

};

#endif
