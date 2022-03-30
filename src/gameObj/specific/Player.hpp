#ifndef PLAYER_HH_
#define PLAYER_HH_
#include "../generic/GameObject.hpp"

class Player : public GameObject {
public:
	Player(std::string);
	virtual ~Player();
};

#endif
