#ifndef GAMETEXT_HPP_
#define GAMETEXT_HPP_
#include <iostream>
#include <iomanip>
#include <string>
#include <SFML/Graphics.hpp>
#include "../assets/assets.hh"

class GameText {
public:
	enum HAlign {
		LEFT,
		CENTER,
		RIGHT
	};
	enum VAlign {
		TOP,
		MIDDLE,
		BOTTOM
	};
	enum Size {
		TITLE,
		XL,
		LARGE,
		MEDIUM,
		SMALL,
	};
private:
	static const int FIXED_LINE_HEIGHT = 8;
	std::vector<sf::Text> texts;
	std::vector<std::string> stringLines;
	std::stringstream stringStream;
	
	sf::Vector2f position;
	Size size;
	HAlign hAlign;
	VAlign vAlign;
	float verticalSpacing = 1.0f;
	bool dirty = false;

	float widestLine = 0.f;
	float totalHeight = 0.f;

	void setTexts();
	void setInternalOrigin();
	void setInternalScale();
	void setLinePositions();
public:
	GameText();

	void setText(std::string s);
	void appendText(std::string s);
	void resetText();

	sf::Vector2f getPosition();
	Size getSize();

	void setPosition(sf::Vector2f position);
	void setSize(Size size);
	void setHAlign(HAlign align);
	void setVAlign(VAlign align);
	void move(sf::Vector2f movement);

	void reRender();

	void draw(sf::RenderWindow& window);
};

#endif
