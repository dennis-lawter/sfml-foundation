#include "AttractState.hpp"

AttractState::AttractState() {
	util::setSeed(SEED);
	pressStartText.setHAlign(GameText::CENTER);
	pressStartText.setVAlign(GameText::MIDDLE);
	pressStartText.setPosition({defines::WIDTH/2.f, defines::HEIGHT*(3.f/4.f)});
	pressStartText.setText(PRESS_START);

	this->roundStartTimer = ROUND_START_MAX-1;
	GamePlayState::startRound();
}

void AttractState::processInput(Event& event) {
	switch (event.type) {
	case Event::KeyReleased:
	case Event::JoystickButtonReleased:
		isEnding = true;
		break;
	default:
		break;
	}
}

void AttractState::update(RenderWindow& window) {
	if (didWin || didLose) {
		isEnding = true;
	}
	
	if (INPUT[inputIter] == 'W') {
		defender.fire();
		inputIter++;
	}
	switch(INPUT[inputIter]) {
	case 'A':
		defender.playerIsMovingLeft = true;
		defender.playerIsMovingRight = false;
		break;
	case 'D':
		defender.playerIsMovingLeft = false;
		defender.playerIsMovingRight = true;
		break;
	case ' ':
		defender.playerIsMovingLeft = false;
		defender.playerIsMovingRight = false;
	}
	inputIter++;
	if (inputIter > INPUT.length()) {
		inputIter = 0;
		isEnding = true;
	}

	GamePlayState::update(window);
}

void AttractState::draw(RenderWindow& window) {
	GamePlayState::draw(window);
	pressStartText.draw(window);
}

AttractState::~AttractState() {

}
