#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../util.hh"
#include "../../rendering/SpriteSheet.hpp"

using namespace sf;

class GameObject {
protected:
	SpriteSheet sprite;
	std::string name;
public:
	float speed;

	GameObject(std::string name);

	void update();
	void draw(sf::RenderWindow& window);

	bool testCollision(GameObject& obj);

	FloatRect getHitBox();
	float getX();
	float getY();
	float getWidth();
	float getHeight();

	Vector2f getPosition();
	void setPosition(Vector2f pos);
};

#endif
