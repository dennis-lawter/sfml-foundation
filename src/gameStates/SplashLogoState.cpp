#include "SplashLogoState.hpp"

SplashLogoState::SplashLogoState() {
	logo.setTexture(textures::assets["bitonicsoftlogo"]);
	logo.setScale(4.f, 4.f);
	logo.setOrigin(8.f, 8.f);
	logo.setPosition(defines::WIDTH / 2.f, 80.f);

	bitonic.setText("BitonicSoft");
	bitonic.setHAlign(GameText::CENTER);
	bitonic.setVAlign(GameText::MIDDLE);
	bitonic.setSize(GameText::TITLE);
	bitonic.setPosition({ defines::WIDTH / 2.f, 130.f });

	us.setText("Dennis Lawter\tBryan Barreto\tJames de Mattos");
	us.setHAlign(GameText::CENTER);
	us.setVAlign(GameText::MIDDLE);
	us.setSize(GameText::LARGE);
	us.setPosition({ defines::WIDTH / 2.f, 180.f });
}

void SplashLogoState::processInput(sf::Event& event) {

}

void SplashLogoState::update(sf::RenderWindow& window) {

}

void SplashLogoState::draw(sf::RenderWindow& window) {
	window.draw(logo);
	bitonic.draw(window);
	us.draw(window);
}

SplashLogoState::~SplashLogoState() {

}
