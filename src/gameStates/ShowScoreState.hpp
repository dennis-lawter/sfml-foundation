#ifndef SHOWSCORESTATE_HPP_
#define SHOWSCORESTATE_HPP_
#include "GameState.hpp"

class ShowScoreState : public GameState {
private:
	GameText highScoreTitleText;
	GameText highScoreText;
	const int IDLE_TIMEOUT = 600;
	int idleTimer = 0;
	Vector2f screenCenter = {defines::WIDTH/2.f, defines::HEIGHT/2.f};
	Sound idleScoreTune;
public:
	bool idle = true;

	ShowScoreState();

	void processInput(Event& event);
	void update(RenderWindow& window);
	void draw(RenderWindow& window);

	virtual ~ShowScoreState();
};

#endif
