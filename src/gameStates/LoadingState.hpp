#ifndef LOADINGSTATE_HPP_
#define LOADINGSTATE_HPP_
#include "GameState.hpp"

class LoadingState : public GameState {
private:
	sf::RectangleShape loadingRectangle;
public:
	LoadingState();

	void processInput(sf::Event& event);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	virtual ~LoadingState();
};

#endif
