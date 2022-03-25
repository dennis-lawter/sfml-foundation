#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../resources.hh"
#include "../score.hh"
#include "../util.hh"

using namespace sf;

class GameObject {
protected:
	Sprite sprite;
public:
	float speed;

	GameObject(Texture& texture, float x, float y);

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
