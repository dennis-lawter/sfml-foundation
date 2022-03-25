#ifndef TITLESTATE_HPP_
#define TITLESTATE_HPP_
#include "GameState.hpp"

class TitleState : public GameState {
private:
	GameText drawTitle1;
	GameText pressStart;
	GameText controls;
	GameText boon;
	GameText bane;

	Sprite oneUp;
	Sprite coin;
	Sprite agressive;
	Sprite bomb;
	Sprite curved;
	Sprite missile;
	Sprite passive;
	Sprite punch;
	Sprite speedUp;
	Sprite speedDown;
	Sound titleSound;

	const int BLINKTIMER = 40;
	int blinkBuffer = 0;
	bool isBlink = false;

	const int IDLE_TIMEOUT = 600;
	int idleTimer = 0;
public:
	bool idle = true;
	const int BUFFERTIMER = 90;
	int bufferTick = 0;

	TitleState();

	void processInput(Event& event);
	void update(RenderWindow& window);
	void draw(RenderWindow& window);

	virtual ~TitleState();
};

#endif
