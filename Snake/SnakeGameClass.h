#pragma once
#include <SFML/Graphics.hpp>
#include "MapClass.h"
#include "FoodClass.h"
#include "SnakeClass.h"
#include "GameStateClass.h"
#include "constants.h"

class SnakeGameClass{
private:
	MapClass map;
	SnakeClass *snake;
	FoodClass food;
	int numMoves;
public:
	void reset();
	SnakeGameClass();
	SnakeGameClass(sf::RenderWindow &window);
	~SnakeGameClass();
	bool moveSnake(int nextMove);
	void draw(sf::RenderWindow &window);
	GameStateClass getState();
	int getMapWidth();
	int getMapHeight();
};

