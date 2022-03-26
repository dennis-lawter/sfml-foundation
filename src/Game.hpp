#ifndef GAME_HPP_
#define GAME_HPP_
#include "defines.hh"
#include "gameStates/LoadingState.hpp"
#include "gameStates/SplashLogoState.hpp"

class Game {
private:
	sf::RenderWindow window;
	sf::View camera;
	sf::RectangleShape background;
	GameState* gameState = nullptr;
	GameState::State currentGameState = GameState::Loading;
	sf::Color screenClearColor; //(0x000022ff)
	sf::Event currentEvent;

	void initializeWindow();
	void resizeWindow();

	void gameLoop();
	void processInputLoop();
	void update();
	void draw();
public:
	bool isRunning = true;

	Game();

	void run();

	virtual ~Game();
};

#endif
