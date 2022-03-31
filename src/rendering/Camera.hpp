#ifndef CAMERA_HPP_
#define CAMERA_HPP_
#include <SFML/Graphics.hpp>
#include "../gameObj/generic/GameObject.hpp"
#include "../defines.hh"

class Camera : public sf::View {
private:
	GameObject* followedObject = nullptr;
	sf::Window* window = nullptr;
public:
	Camera();
	
	void setFollowedObject(GameObject* obj);
	GameObject* getFollowedObject();
	void setWindow(sf::Window* window);
	
	void update();
	
	virtual ~Camera();
};

#endif
