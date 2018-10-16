#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/system/Vector2.hpp>
#include <stdlib.h>
#include <ctime>
#include "BoxClass.h"

class MapClass
{
private:
	BoxClass **mapTiles;
	int numAcross;
	int numDown;

	void setExteriorWalls();
public:
	MapClass();
	MapClass(sf::Vector2u windowSize);
	~MapClass();
	void draw(sf::RenderWindow &window);
	sf::Vector2u getRandLocation();
	sf::Vector2u getCenterLocation();
	int changeBoxColor(sf::Vector2u location, int inColor);
};
