#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/system/Vector2.hpp>
#include <stdlib.h>
#include <ctime>
#include "BoxClass.h"
#include "ScoreBoardClass.h"

class MapClass
{
private:
	BoxClass **mapTiles;
	int numAcross;
	int numDown;
	ScoreBoardClass scoreBoard;

	void setExteriorWalls();
public:
	MapClass();
	MapClass(sf::Vector2u windowSize, bool random);
	~MapClass();
	void draw(sf::RenderWindow &window);
	sf::Vector2u getRandLocation();
	sf::Vector2u getCenterLocation();
	int changeBoxColor(sf::Vector2u location, int inColor);
	void updateScore();
};
