#include "SpriteSheet.hpp"

void SpriteSheet::incrementFrame() {
	// int limit = this->animationList
}

SpriteSheet::SpriteSheet(std::string name) {
	this->animationList = &(animations::assets[name]);
	this->animation = this->animationList->defaultAnimation;
	// std::cout << this->animation << endl;
	this->setTexture(textures::assets[name]);
	this->setAnimation(this->animation);
	sf::IntRect rect = this->animationList->getSheetBox(this->animation, this->keyFrame);
	this->setTextureRect(rect);
}

void SpriteSheet::update() {
	this->timer++;
	if (this->timer >= this->animationList->framesPer) {
		if (keyFrame + 1 >= this->animationList->getKeyFrameCount(animation)) {
			keyFrame = 0;
		} else {
			keyFrame++;
		}
		sf::IntRect rect = this->animationList->getSheetBox(this->animation, this->keyFrame);
		this->setTextureRect(rect);
		this->timer = 0;
	}
}

void SpriteSheet::setAnimation(std::string animation) {
	this->animation = animation;
}

SpriteSheet::~SpriteSheet() {
}
