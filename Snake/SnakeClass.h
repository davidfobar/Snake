#pragma once
#include "MapClass.h"
#include "SnakeBodyNodeClass.h"
#include <SFML/system/Vector2.hpp>
#include "constants.h"

class SnakeClass
{
private:
	int snakeLength;
	int prevDir;
	SnakeBodyNodeClass* headNode;
	SnakeBodyNodeClass* tailNode;
	
public:
	SnakeClass();
	SnakeClass(MapClass &map);
	~SnakeClass();
	int move(MapClass &map, int dir);
	sf::Vector2u getHeadLocation();
};

