#include "FoodClass.h"

FoodClass::FoodClass(){
}

void FoodClass::createNew(MapClass &curMap) {
	foodLoc = curMap.getRandLocation();
	curMap.changeBoxColor(foodLoc, BLUE);
}

FoodClass::~FoodClass()
{
}
