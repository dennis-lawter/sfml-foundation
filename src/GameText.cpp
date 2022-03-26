#include "GameText.hpp"

std::map<GameText::Size, float> scaleFactor = {
	{GameText::TITLE, .12f},
	{GameText::XL, .10f},
	{GameText::LARGE, .08f},
	{GameText::MEDIUM, .05f},
	{GameText::SMALL, .03f}
};

GameText::GameText() {
	this->position = { 0.f, 0.f };
	this->size = GameText::MEDIUM;
	this->hAlign = GameText::LEFT;
	this->vAlign = GameText::TOP;
	this->stringStream.clear();
}

void GameText::setTexts() {
	std::string temp;
	std::string keepValue = stringStream.str();
	stringStream << "\n";

	texts.clear();
	while (std::getline(stringStream, temp, '\n')) {
		texts.emplace_back(temp, fonts::assets["press-start-2p"], 80U);
	}
	stringStream.clear();
	stringStream.str("");
	stringStream << keepValue;
}

void GameText::setInternalOrigin() {
	widestLine = 0.f;
	totalHeight = 0.f;
	for (sf::Text& text : texts) {
		sf::FloatRect textBounds = text.getLocalBounds();
		float fullWidth = textBounds.left + textBounds.width;
		if (fullWidth > widestLine) {
			widestLine = fullWidth;
		}
		if (textBounds.top > 0.f) {
			totalHeight += (FIXED_LINE_HEIGHT + verticalSpacing) * 10.f;
		} else if (textBounds.height > 0.f) {
			totalHeight += (FIXED_LINE_HEIGHT + verticalSpacing) * 10.f;
		}
	}
	sf::Vector2f origin;
	switch (hAlign) {
	case LEFT:
		origin.x = 0.f;
		break;
	case CENTER:
		origin.x = widestLine / 2.f;
		break;
	case RIGHT:
		origin.x = widestLine;
		break;
	}
	switch (vAlign) {
	case TOP:
		origin.y = 0.f;
		break;
	case MIDDLE:
		origin.y = totalHeight / 2.f;
		break;
	case BOTTOM:
		origin.y = totalHeight;
		break;
	}
	for (sf::Text& text : texts) {
		text.setOrigin(origin);
	}
}

void GameText::setInternalScale() {
	float scale = scaleFactor[size];
	for (sf::Text& text : texts) {
		text.setScale(scale, scale);
	}
}

void GameText::setLinePositions() {
	float heightOffset = 0.f;
	float scale = scaleFactor[size];
	sf::Vector2f tempPosition = this->position;
	for (sf::Text& text : texts) {
		sf::FloatRect localBounds = text.getLocalBounds();
		switch(hAlign){
		case LEFT:
			tempPosition.x = this->position.x;
			break;
		case CENTER:
			tempPosition.x = this->position.x - scale*(localBounds.width-widestLine)/2.f;
			break;
		case RIGHT:
			tempPosition.x = this->position.x - scale*(localBounds.width-widestLine);
			break;
		}
		tempPosition.y += heightOffset;
		text.setPosition(tempPosition);
		heightOffset = scale * (FIXED_LINE_HEIGHT + verticalSpacing) * 10.f;
	}
}

void GameText::reRender() {
	setTexts();
	setInternalOrigin();
	setInternalScale();
	setLinePositions();

	this->dirty = false;
}

void GameText::setText(std::string s) {
	this->stringStream.clear();
	this->stringStream.str("");
	this->stringStream << s;
	this->dirty = true;
}

void GameText::appendText(std::string s) {
	this->stringStream << s;
	this->dirty = true;
}

void GameText::resetText() {
	this->stringStream.str("");
	this->dirty = true;
}

void GameText::setPosition(sf::Vector2f position) {
	this->position = position;
	this->dirty = true;
}

void GameText::setSize(Size size) {
	this->size = size;
	this->dirty = true;
}

void GameText::setHAlign(HAlign align) {
	this->hAlign = align;
	this->dirty = true;
}

void GameText::setVAlign(VAlign align) {
	this->vAlign = align;
	this->dirty = true;
}

void GameText::move(sf::Vector2f movement) {
	for (sf::Text& text : texts) {
		text.move(movement);
	}
}

sf::Vector2f GameText::getPosition() {
	return this->position;
}

GameText::Size GameText::getSize() {
	return this->size;
}

void GameText::draw(sf::RenderWindow& window) {
	if (this->dirty) {
		this->reRender();
	}
	if (texts.size() <= 0) return;
	for (sf::Text& text : texts) {
		window.draw(text);
	}
}
