#ifndef PLAYERINPUT_HH_
#define PLAYERINPUT_HH__

#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "util.hh"

namespace playerInput {
	sf::Vector2f getInputVector();
	void inputSideScroll(sf::Event& event);
	void inputTopDown(sf::Event& event);
}

#endif
