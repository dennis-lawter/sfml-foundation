#include "EnterInitialsState.hpp"

EnterInitialsState::EnterInitialsState() {
	newHighScoreText.setPosition({ screenCenter.x, 15.f });
	newHighScoreText.setHAlign(GameText::CENTER);
	newHighScoreText.setSize(GameText::HUGE);
	newHighScoreText.setText("NEW HIGH SCORE");

	instructionsText.setPosition({ screenCenter.x, 30.f });
	instructionsText.setHAlign(GameText::CENTER);
	instructionsText.setText("ENTER INITIALS");

	playerEnteredText.setPosition(screenCenter);
	playerEnteredText.setHAlign(GameText::CENTER);
	playerEnteredText.setVAlign(GameText::MIDDLE);
	playerEnteredText.setSize(GameText::TITLE);
	playerEnteredText.setText(playerInitials);

	fanfare.setBuffer(resources::soundFile["newhighscore"]);
	fanfare.play();

	accept.setBuffer(resources::soundFile["accept"]);
	backspace.setBuffer(resources::soundFile["backspace"]);
	blip.setBuffer(resources::soundFile["blip"]);
}

void EnterInitialsState::updateEnteredText() {
	if (currentCharIndex > 3) return;
	if (isBlink) {
		playerInitials[currentCharIndex] = ' ';
		playerEnteredText.setText(playerInitials);
	} else {
		playerInitials[currentCharIndex] = displayedChar;
		playerEnteredText.setText(playerInitials);
	}
	playerInitials[currentCharIndex] = displayedChar;
}

void EnterInitialsState::playerPressedUp() {
	if (displayedChar == '_') {
		displayedChar = 'A';
	} else if (displayedChar == 'Z') {
		displayedChar = 'A';
	} else {
		displayedChar++;
	}
	blip.play();
	updateEnteredText();
}

void EnterInitialsState::playerPressedDown() {
	if (displayedChar == '_') {
		displayedChar = 'Z';
	} else if (displayedChar == 'A') {
		displayedChar = 'Z';
	} else {
		displayedChar--;
	}
	blip.play();
	updateEnteredText();
}

void EnterInitialsState::playerPressedAccept() {
	if (displayedChar == '_') return;
	
	if (currentCharIndex >= 3) {
		score::initials = playerInitials.substr(1, 3);
		isEnding = true;
		return;
	}
	accept.play();
	currentCharIndex++;
	updateEnteredText();
}

void EnterInitialsState::playerPressedBackspace() {
	if (currentCharIndex <= 1) {
		return;
	} else if (currentCharIndex <= 3) {
		playerInitials[currentCharIndex] = '_';
	}
	backspace.play();
	currentCharIndex--;
	updateEnteredText();
}

void EnterInitialsState::processInput(Event& event) {
	int joystickId = -1;
	switch (event.type) {
	case Event::JoystickButtonPressed:
		switch (event.joystickButton.button) {
		case 0:
			playerPressedAccept();
			break;
		case 1:
			playerPressedBackspace();
			break;
		case 2:
		case 3:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			break;
		default:
			break;
		}
		break;
	case Event::JoystickMoved:
		joystickId = event.joystickMove.joystickId;
		if (isJoyStickCentered) {
			if (
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) < -50 ||
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) < -50
			) {
				isJoyStickCentered = false;
				playerPressedBackspace();
				break;
			} else if (
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) > 50 ||
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) > 50
			) {
				isJoyStickCentered = false;
				playerPressedAccept();
				break;
			} else if (
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y) < -50 ||
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) < -50
			) {
				isJoyStickCentered = false;
				playerPressedUp();
				break;
			}  else if (
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y) > 50 ||
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) > 50
			) {
				isJoyStickCentered = false;
				playerPressedDown();
				break;
			}
		} else if (
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) > -30 &&
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) < 30 &&
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y) > -30 &&
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y) < 30 &&
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) > -30 &&
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) < 30 &&
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) > -30 &&
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) < 30
		) {
			isJoyStickCentered = true;
			break;
		}
		break;
	case Event::KeyPressed:
		switch (event.key.code) {
		case Keyboard::Left:
		case Keyboard::Backspace:
		case Keyboard::A:
			playerPressedBackspace();
			break;
		case Keyboard::Right:
		case Keyboard::Space:
		case Keyboard::Enter:
		case Keyboard::D:
			playerPressedAccept();
			break;
		case Keyboard::W:
		case Keyboard::Up:
			playerPressedUp();
			break;
		case Keyboard::S:
		case Keyboard::Down:
			playerPressedDown();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void EnterInitialsState::update(RenderWindow& window) {
	isBlinkTimer++;
	if (
		(!isBlink && isBlinkTimer >= BLINK_TIMEOUT) ||
		(isBlink && isBlinkTimer >= BLINK_TIMEOUT / 2)
		) {
		isBlink = !isBlink;
		isBlinkTimer = 0;
		updateEnteredText();
	}
}

void EnterInitialsState::draw(RenderWindow& window) {
	newHighScoreText.draw(window);
	instructionsText.draw(window);
	playerEnteredText.draw(window);
}

EnterInitialsState::~EnterInitialsState() {}
