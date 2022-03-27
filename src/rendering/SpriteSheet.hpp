#ifndef SPRITESHEET_HPP_
#define SPRITESHEET_HPP_
#include <SFML/Graphics.hpp>
#include "../assets/assets.hh"

class SpriteSheet : public sf::Sprite {
private:
	AnimationList* animationList;
	unsigned int timer = 0;
	unsigned int keyFrame = 0;
	std::string animation = "";

	void incrementFrame();
public:
	SpriteSheet(std::string name);

	void update();
	void setAnimation(std::string animation);

	~SpriteSheet();
};

#endif
