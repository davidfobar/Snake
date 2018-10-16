#pragma once
#include "MapClass.h"
#include "SnakeBodyNodeClass.h"
#include <SFML/system/Vector2.hpp>

const int GAME_OVER = 99;
const int EAT_FOOD = 10;
const int CLEAR = 11;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

class SnakeClass
{
private:
	int snakeLength;
	SnakeBodyNodeClass* headNode;
	SnakeBodyNodeClass* tailNode;
	
public:
	SnakeClass();
	SnakeClass(MapClass &map);
	~SnakeClass();

	int move(MapClass &map, int dir);
};

