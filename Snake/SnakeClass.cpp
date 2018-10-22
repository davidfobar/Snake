#include "SnakeClass.h"

SnakeClass::SnakeClass(){
	
}

SnakeClass::SnakeClass(MapClass &map){
	snakeLength = 2;
	sf::Vector2u centerOfMap = map.getCenterLocation();
	headNode = new SnakeBodyNodeClass;
	tailNode = new SnakeBodyNodeClass;
	headNode->setLocation(centerOfMap);
	map.changeBoxColor(centerOfMap, RED);
	centerOfMap.x++;
	tailNode->setLocation(centerOfMap);
	map.changeBoxColor(centerOfMap, WHITE);
	
	headNode->setPrev(tailNode);
	headNode->setNext(nullptr);
	tailNode->setNext(headNode);
	tailNode->setPrev(nullptr);
}

int SnakeClass::move(MapClass &map, int dir) {
	int moveResult = CLEAR;

	sf::Vector2u headLocation = headNode->getLocation();
	map.changeBoxColor(headLocation, WHITE);

	if(dir == UP) headLocation.x--;
	else if (dir == DOWN) headLocation.x++;
	else if (dir == LEFT) headLocation.y--;
	else if (dir == RIGHT) headLocation.y++;

	SnakeBodyNodeClass *newHead = new SnakeBodyNodeClass;
	moveResult = map.changeBoxColor(headLocation, RED);
	newHead->setLocation(headLocation);

	SnakeBodyNodeClass *oldHead = headNode;
	headNode = newHead;
	newHead->setPrev(oldHead);
	oldHead->setNext(newHead);
	newHead->setNext(nullptr);

	if (moveResult == WHITE) {
		moveResult = GAME_OVER;
	}
	else if (moveResult == BLUE) {
		moveResult = EAT_FOOD;
		map.updateScore();
	}
	else {
		map.changeBoxColor(tailNode->getLocation(), BLACK);
		SnakeBodyNodeClass *oldTail = tailNode;
		tailNode = oldTail->getNext();
		delete oldTail;
		tailNode->setPrev(nullptr);
	}

	return moveResult;
}

SnakeClass::~SnakeClass()
{
}
