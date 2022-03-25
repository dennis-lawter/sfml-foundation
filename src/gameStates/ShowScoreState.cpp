#include "ShowScoreState.hpp"

ShowScoreState::ShowScoreState() {
	highScoreText = score::getScoreTextBlock();
	highScoreText.reRender();
	highScoreText.move({0.f, 600.f});

	highScoreTitleText.setPosition({screenCenter.x, 15.f});
	highScoreTitleText.setHAlign(GameText::CENTER);
	highScoreTitleText.setSize(GameText::TITLE);
	highScoreTitleText.setText("HIGH SCORES");

	idleScoreTune.setBuffer(resources::soundFile["idlescorelist"]);
	idleScoreTune.play();
}

void ShowScoreState::processInput(Event& event) {
	switch (event.type) {
	case Event::KeyReleased:
	case Event::JoystickButtonReleased:
		isEnding = true;
		idle = false;
		break;
	default:
		break;
	}
}

void ShowScoreState::update(RenderWindow& window) {
	if (idleTimer < IDLE_TIMEOUT) {
		idleTimer++;
	} else if (isEnding != true) {
		isEnding = true;
		idle = true;
	}
	
	int endAnimation = IDLE_TIMEOUT / 4;

	if (idleTimer < endAnimation) {
		highScoreText.move({0.f, -4.f});
	}
}

void ShowScoreState::draw(RenderWindow& window) {
	highScoreTitleText.draw(window);
	highScoreText.draw(window);
}

ShowScoreState::~ShowScoreState() {}
