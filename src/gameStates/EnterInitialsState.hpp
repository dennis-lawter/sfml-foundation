#ifndef ENTERINITIALSSTATE_HPP_
#define ENTERINITIALSSTATE_HPP_
#include "GameState.hpp"

class EnterInitialsState : public GameState {
private:
	GameText newHighScoreText;
	GameText instructionsText;
	GameText playerEnteredText;
	string playerInitials = " ___ ";
	Vector2f screenCenter = {defines::WIDTH/2.f, defines::HEIGHT/2.f};
	Sound fanfare;
	Sound accept;
	Sound backspace;
	Sound blip;
	bool isBlink = false;
	const int BLINK_TIMEOUT = 10;
	int isBlinkTimer = 0;
	char displayedChar = '_';
	int currentCharIndex = 1;
	bool isJoyStickCentered = false;

	void updateEnteredText();

	void playerPressedUp();
	void playerPressedDown();
	void playerPressedAccept();
	void playerPressedBackspace();
public:
	EnterInitialsState();

	void processInput(Event& event);
	void update(RenderWindow& window);
	void draw(RenderWindow& window);

	virtual ~EnterInitialsState();
};

#endif
