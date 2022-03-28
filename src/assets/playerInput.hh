#ifndef PLAYERINPUT_HH_
#define PLAYERINPUT_HH__

#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace playerInput {

	sf::Vector2f inputSideScroll(sf::Event& event);
	sf::Vector2f inputTopDown(sf::Event& event);
}

#endif
