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
	int _x;
	int _y;
	ScoreBoardClass scoreBoard;
	void setExteriorWalls();
public:
	MapClass();
	MapClass(sf::Vector2u windowSize, bool random);
	~MapClass();
	void draw(sf::RenderWindow &window);
	sf::Vector2u getRandLocation();
	sf::Vector2u getCenterLocation();
	sf::Vector2u getSize();
	int changeBoxColor(sf::Vector2u location, int inColor);
	void updateScore(int val);
	void reset();
	int getScore();
	int getNearestPosX(sf::Vector2u location);
	int getNearestPosY(sf::Vector2u location);
	int getNearestNegX(sf::Vector2u location);
	int getNearestNegY(sf::Vector2u location);
};
