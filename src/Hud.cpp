#include "Hud.hpp"

Hud::Hud() {
	lastCheckedScore = score::score;
	lives.setTexture(resources::textures["1up"]);

	text.setHAlign(GameText::LEFT);
	text.setVAlign(GameText::TOP);
	text.setSize(GameText::HUGE);
	text.setPosition(Vector2f(2.f, 1.f));

	updateScore();
}

void Hud::draw(RenderWindow& window) {
	text.draw(window);

	for (int i = 0; i < score::currentLives; i++) {
		lives.setPosition(120 - (9 * i), 0);
		window.draw(lives);
	}
}

void Hud::updateScore() {
	scoreOut.str("");
	scoreOut << setfill('0') << setw(8) << lastCheckedScore;
	string scoreOutString = scoreOut.str();
	text.setText(scoreOutString);
}

void Hud::update() {
	if (score::score < lastCheckedScore) {
		lastCheckedScore -= 4;
		if (lastCheckedScore < score::score) {
			lastCheckedScore = score::score;
		}
		updateScore();
	} else if (score::score > lastCheckedScore) {
		lastCheckedScore += 4;
		if (lastCheckedScore > score::score) {
			lastCheckedScore = score::score;
		}
		updateScore();
	}
}

void Hud::indicateGlobalScoreChange(ParticleGroup& particleGroup, int scoreChange) {
	string indication = "";
	Color color;
	if (scoreChange > 0) {
		indication = "+";
		color = Color::Cyan;
	} else if (scoreChange < 0) {
		indication = "";
		color = Color::Red;
	} else {
		return;
	}
	indication += to_string(scoreChange);
	particleGroup.createParticleText(indication, {75.f, 8.f}, color);
}
