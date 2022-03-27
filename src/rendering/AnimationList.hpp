#ifndef ANIMATIONLIST_HPP_
#define ANIMATIONLIST_HPP_
#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class AnimationList {
private:
	std::map<std::string, std::vector<sf::Vector2i>> animations;
public:
	std::string textureName = "";
	std::string defaultAnimation = "";
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int framesPer = 1;

	AnimationList();

	void addCompleteList(std::string name, std::vector<sf::Vector2i> coords);
	void createEmptyList(std::string name);
	void appendToList(std::string name, sf::Vector2i coordPair);

	unsigned int getKeyFrameCount(std::string name);
	sf::Vector2i getCoordPair(std::string name, unsigned int keyFrame);
	sf::IntRect getSheetBox(std::string name, unsigned int keyFrame);
	
	~AnimationList();
};

#endif
