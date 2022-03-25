#ifndef GAMETEXT_HPP_
#define GAMETEXT_HPP_
#include <iostream>
#include <iomanip>
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

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
		HUGE,
		LARGE,
		MEDIUM,
		SMALL,
	};
private:
	static const int FIXED_LINE_HEIGHT = 8;
	vector<Text> texts;
	vector<string> stringLines;
	stringstream stringStream;
	
	Vector2f position;
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

	void setText(string s);
	void appendText(string s);
	void resetText();

	Vector2f getPosition();
	Size getSize();

	void setPosition(Vector2f position);
	void setSize(Size size);
	void setHAlign(HAlign align);
	void setVAlign(VAlign align);
	void move(Vector2f movement);

	void reRender();

	void draw(RenderWindow& window);
};

#endif
