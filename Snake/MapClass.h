#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/system/Vector2.hpp>
#include <stdlib.h>
#include <ctime>
#include "BoxClass.h"
#include "ScoreBoardClass.h"
#include "GameStateClass.h"
#include <vector>

class MapClass{
private:
	BoxClass **mapTiles;
	int _x;
	int _y;
	ScoreBoardClass scoreBoard;
	void setExteriorWalls();
public:
	MapClass();
	MapClass(sf::Vector2u windowSize);
	~MapClass();
	void draw(sf::RenderWindow &window);
	sf::Vector2u getRandLocation();
	sf::Vector2u getCenterLocation();
	sf::Vector2u getSize();
	int changeBoxColor(sf::Vector2u location, int inColor);
	void updateScore(int val);
	void reset();
	int getScore();
	vector<double> getFullMapState();
};
