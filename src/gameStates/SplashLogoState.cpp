#include "SplashLogoState.hpp"

SplashLogoState::SplashLogoState() {
	initialColor = sf::Color(0xFFFFFF00);
	finalColor = sf::Color(0xFFFFFFFF);
	currentColor = initialColor;

	initialScale = { 4.f, 4.f };
	curretScale = initialScale;

	logo.setTexture(textures::assets["bitonicsoftlogo"]);
	logo.setScale(initialScale);
	logo.setOrigin(8.f, 16.f);
	logo.setPosition(defines::WIDTH / 2.f, 100.f);
	logo.setColor(initialColor);

	bitonic.setText("BitonicSoft");
	bitonic.setHAlign(GameText::CENTER);
	bitonic.setVAlign(GameText::MIDDLE);
	bitonic.setSize(GameText::TITLE);
	bitonic.setPosition({ defines::WIDTH / 2.f, 130.f });
	bitonic.setColor(initialColor);

	us.setText("Dennis Lawter\tBryan Barreto\tJames de Mattos");
	us.setHAlign(GameText::CENTER);
	us.setVAlign(GameText::MIDDLE);
	us.setSize(GameText::LARGE);
	us.setPosition({ defines::WIDTH / 2.f, 180.f });
	us.setColor(initialColor);
}

void SplashLogoState::processInput(sf::Event& event) {

}

void SplashLogoState::update(sf::RenderWindow& window) {
	if (timer < FADE_IN_MAX) {
		float fadeProgress = timer / (float)FADE_IN_MAX;
		currentColor.a = util::lerp(initialColor.a, finalColor.a, fadeProgress);

		logo.setColor(currentColor);
		bitonic.setColor(currentColor);
		us.setColor(currentColor);
	}
	if (timer > STRETCH_WIDE_START && timer < STRETCH_WIDE_END) {
		float stretchProgress = (timer  - STRETCH_WIDE_START) / (float)(STRETCH_WIDE_END - STRETCH_WIDE_START);
		curretScale.x = util::lerp(initialScale.x, WIDE_SCALE.x, stretchProgress);
		curretScale.y = util::lerp(initialScale.y, WIDE_SCALE.y, stretchProgress);

		logo.setScale(curretScale);
	}

	if (timer >= STATE_END) {
		this->isEnding = true;
	}

	timer++;
}

void SplashLogoState::draw(sf::RenderWindow& window) {
	window.draw(logo);
	bitonic.draw(window);
	us.draw(window);
}

SplashLogoState::~SplashLogoState() {

}
