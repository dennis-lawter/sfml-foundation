#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../util.hh"
#include "../../rendering/SpriteSheet.hpp"

class GameObject {
protected:
	SpriteSheet sprite;
	nlohmann::json customProperties;
public:
	float speed;
	std::string name;
	sf::Vector2f oldPosition;

	GameObject(std::string name);

	virtual void update();
	void draw(sf::RenderWindow& window);

	bool testCollision(GameObject& obj);
	bool testCollision(sf::FloatRect& rect);

	virtual sf::FloatRect getHitBox();
	float getX();
	float getY();
	float getWidth();
	float getHeight();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	nlohmann::json getCustomProperty(std::string name);
	void setCustomProperty(std::string name, nlohmann::json value);

	virtual ~GameObject();
};

#endif
