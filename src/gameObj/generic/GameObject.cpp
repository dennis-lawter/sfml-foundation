#include "GameObject.hpp"
GameObject::GameObject(std::string name) {
	this->name = name;
}

void GameObject::draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
}

bool GameObject::testCollision(GameObject& obj) {
	return getHitBox().intersects(obj.getHitBox());
}

FloatRect GameObject::getHitBox() {
	return this->sprite.getGlobalBounds();
}

// get current x position of object from the top left pixel of the object
float GameObject::getX() {
	return this->sprite.getPosition().x;
}

// get current y position of object from the top left pixel of the object
float GameObject::getY() {
	return this->sprite.getPosition().y;
}

float GameObject::getWidth() {
	return this->sprite.getLocalBounds().width;
}

float GameObject::getHeight() {
	return this->sprite.getLocalBounds().height;
}

Vector2f GameObject::getPosition() {
	return sprite.getPosition();
}

void GameObject::setPosition(Vector2f pos) {
	sprite.setPosition(pos);
}
