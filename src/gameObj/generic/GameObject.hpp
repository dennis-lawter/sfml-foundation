#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../util.hh"
#include "../../rendering/SpriteSheet.hpp"

class GameObject {
protected:
	SpriteSheet sprite;
public:
	float speed;
	std::string name;

	GameObject(std::string name);

	void update();
	void draw(sf::RenderWindow& window);

	bool testCollision(GameObject& obj);

	sf::FloatRect getHitBox();
	float getX();
	float getY();
	float getWidth();
	float getHeight();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
};

#endif
