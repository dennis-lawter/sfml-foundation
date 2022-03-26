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
	sf::Sound sound;
	GameText bitonic;
	GameText us;

	sf::Vector2f initialScale;
	sf::Vector2f curretScale;
	const sf::Vector2f WIDE_SCALE = { 7.f, 2.f };
	const sf::Vector2f HEIGHT_SCALE = { 2.f, 7.f };

	int timer = 0;
	const int FADE_IN_MAX = 30;
	const int STRETCH_WIDE_START = 30;
	const int STRETCH_WIDE_END = 40;
	const int STRETCH_TALL_START = 40;
	const int STRETCH_TALL_END = 50;
	const int STRETCH_NORMAL_START = 50;
	const int STRETCH_NORMAL_END = 60;
	const int STATE_END = 120;

	const int PLAY_SOUND = 30;

public:
	SplashLogoState();

	void processInput(sf::Event& event);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	virtual ~SplashLogoState();

};

#endif
