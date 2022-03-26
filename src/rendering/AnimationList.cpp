#include "AnimationList.hpp"

AnimationList::AnimationList() {
}

void AnimationList::addCompleteList(std::string name, std::vector<sf::Vector2i> coords) {
	this->createEmptyList(name);
	for (sf::Vector2i coordPair : coords) {
		this->appendToList(name, coordPair);
	}
}

void AnimationList::createEmptyList(std::string name) {
	animations.emplace(name, std::vector<sf::Vector2i>{});
}

void AnimationList::appendToList(std::string name, sf::Vector2i coordPair) {
	animations[name].push_back(coordPair);
}

AnimationList::~AnimationList() {
}
