#pragma once
#include <SFML/Graphics.hpp>
#include "MapClass.h"
#include "FoodClass.h"
#include "SnakeClass.h"

const bool ENABLE_RANDOM = false;

class SnakeGameClass
{
private:
	MapClass map;
	SnakeClass *snake;
	FoodClass food;
public:
	void reset();
	SnakeGameClass();
	SnakeGameClass(sf::RenderWindow &window);
	~SnakeGameClass();
	void moveSnake(int nextMove);
	void draw(sf::RenderWindow &window);
	int getScore();
	uint8_t* getState();
	int getMapWidth();
	int getMapHeight();
};

