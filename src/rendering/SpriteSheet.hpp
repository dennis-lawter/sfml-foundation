#ifndef SPRITESHEET_HPP_
#define SPRITESHEET_HPP_
#include <SFML/Graphics.hpp>
#include "AnimationList.hpp"

class SpriteSheet : public sf::Sprite {
private:
	AnimationList* animationList;
public:
	SpriteSheet(std::string name);

	~SpriteSheet();
};

#endif
