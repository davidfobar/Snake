#pragma once
#include "MapClass.h"

class FoodClass
{
private:
	sf::Vector2u foodLoc;
public:
	FoodClass();
	void createNew(MapClass &curMap);
	~FoodClass();
};

