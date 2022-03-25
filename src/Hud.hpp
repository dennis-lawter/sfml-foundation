#ifndef HUD_HPP_
#define HUD_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include "resources.hh"
#include "score.hh"
using namespace sf;
using namespace std;
#include "GameText.hpp"
#include "gameObj/groups/ParticleGroup.hpp"


class Hud {
private:
	Font& font = resources::font;
	stringstream scoreOut;
	int lastCheckedScore;
	Sprite lives;
	GameText text;

	void updateScore();
public:
	Hud();
	void draw(RenderWindow& window);
	void update();
	void indicateGlobalScoreChange(ParticleGroup& particleGroup, int increase);
};

#endif
