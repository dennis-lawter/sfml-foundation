#include "Camera.hpp"

Camera::Camera() {
	this->followedObject = nullptr;
	this->window = nullptr;
}

void Camera::setFollowedObject(GameObject* obj) {
	this->followedObject = obj;
}

GameObject* Camera::getFollowedObject() {
	return this->followedObject;
}

void Camera::setWindow(sf::Window* window) {
	this->window = window;
}

void Camera::update() {
	// if (this->window) {
	// 	float winW = this->window->getSize().x;
	// 	float winH = this->window->getSize().y;
	// 	float w,h,goalSizePixels,x,y;
	// 	float aspectRatio = ((float) defines::WIDTH)/defines::HEIGHT;
		
	// 	if (winW/winH > aspectRatio) {
	// 		// too wide, get w<=1
	// 		goalSizePixels = winH*aspectRatio;
	// 		w = goalSizePixels / winW;
	// 		x = (1.0-w)/2.0;
	// 		h = 1.0;
	// 		y = 0.0;
	// 	} else {
	// 		// too tall, get h<=1
	// 		goalSizePixels = winW*(1.0/aspectRatio);
	// 		h = goalSizePixels / winH;
	// 		y = (1.0-h)/2.0;
	// 		w = 1.0;
	// 		x = 0.0;
	// 	}
	// 	sf::FloatRect rect (x, y, w, h);
	// 	this->setViewport(rect);
	// }
	if (this->followedObject) {
		this->setCenter(followedObject->getPosition());
	}
}

Camera::~Camera() {
}
