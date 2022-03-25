#include "GameOverState.hpp"

GameOverState::GameOverState() {
	score::addScore();
	gameOverSound.setBuffer(resources::soundFile["gameover"]);
	gameOverSound.play();

	highScoreText = score::getScoreTextBlock();

	gameOverText.setHAlign(GameText::CENTER);
	gameOverText.setSize(GameText::TITLE);
	gameOverText.setPosition({defines::WIDTH/2.f, 15.f});
	gameOverText.setText(gameOver);

	pressAnyKeyText.setHAlign(GameText::CENTER);
	pressAnyKeyText.setPosition({defines::WIDTH/2.f, 110.f});
	pressAnyKeyText.setText(pressAnyKey);
}

void GameOverState::processInput(Event& event) {
	switch (event.type) {
	case Event::JoystickButtonPressed:
	case Event::KeyPressed:
		holdBuffer = false;
		break;
	case Event::KeyReleased:
	case Event::JoystickButtonReleased:
		if (!holdBuffer && bufferTick == BUFFERTIMER) {
			isEnding = true;
		}
		break;
	default:
		break;
	}
}

void GameOverState::draw(RenderWindow& window) {
	hud.draw(window);

	highScoreText.draw(window);
	gameOverText.draw(window);

	if (isTextHidden && bufferTick >= BUFFERTIMER) {
		pressAnyKeyText.draw(window);
	}
}

void GameOverState::update(RenderWindow& window) {
	if (blinkBuffer < BLINKTIMER) {
		blinkBuffer++;
	} else {
		isTextHidden = !isTextHidden;
		string scoreString = score::getScoreTextString(isTextHidden);
		highScoreText.setText(scoreString);
		blinkBuffer = 0;
	}
	if (bufferTick < BUFFERTIMER) {
		bufferTick++;
	}
}

GameOverState::~GameOverState() {
}
