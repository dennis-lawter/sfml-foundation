#include "GameObject.hpp"
GameObject::GameObject(std::string name)
: sprite(name) {
	this->name = name;
	this->sprite.update();
	sf::FloatRect rect = this->getHitBox();
	this->sprite.setOrigin(rect.width/2.f, rect.height/2.f);
}

void GameObject::draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
}

void GameObject::update() {
	this->sprite.update();
}

bool GameObject::testCollision(GameObject& obj) {
	return getHitBox().intersects(obj.getHitBox());
}

sf::FloatRect GameObject::getHitBox() {
	return this->sprite.getGlobalBounds();
}

float GameObject::getX() {
	return this->sprite.getPosition().x;
}

float GameObject::getY() {
	return this->sprite.getPosition().y;
}

float GameObject::getWidth() {
	return this->sprite.getLocalBounds().width;
}

float GameObject::getHeight() {
	return this->sprite.getLocalBounds().height;
}

sf::Vector2f GameObject::getPosition() {
	return sprite.getPosition();
}

void GameObject::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}
