#include "AnimationList.hpp"
#include <iostream>

AnimationList::AnimationList() {
}

void AnimationList::addCompleteList(std::string name, std::vector<sf::Vector2i> coords) {
	this->createEmptyList(name);
	for (sf::Vector2i coordPair : coords) {
		this->appendToList(name, coordPair);
	}
}

void AnimationList::createEmptyList(std::string name) {
	this->animations.emplace(name, std::vector<sf::Vector2i>{});
}

void AnimationList::appendToList(std::string name, sf::Vector2i coordPair) {
	this->animations[name].push_back(coordPair);
}

unsigned int AnimationList::getKeyFrameCount(std::string name) {
	return this->animations[name].size();
}

sf::Vector2i AnimationList::getCoordPair(std::string name, unsigned int keyFrame) {
	return animations[name][keyFrame];
}

sf::IntRect AnimationList::getSheetBox(std::string name, unsigned int keyFrame) {
	sf::IntRect rect;
	sf::Vector2i coordPair = this->getCoordPair(name, keyFrame);
	rect.left = coordPair.x * this->width;
	rect.top = coordPair.y * this->height;
	rect.width = this->width;
	rect.height = this->height;
	return rect;
}

AnimationList::~AnimationList() {
}
