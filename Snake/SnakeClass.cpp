#include "SnakeClass.h"
#include <iostream>
using namespace std;

SnakeClass::SnakeClass(){}

SnakeClass::SnakeClass(MapClass &map){
	snakeLength = 2;
	prevDir = UP;
	sf::Vector2u centerOfMap = map.getCenterLocation();
	headNode = new SnakeBodyNodeClass;
	tailNode = new SnakeBodyNodeClass;
	headNode->setLocation(centerOfMap);
	map.changeBoxColor(centerOfMap, RED);
	tailNode->setLocation(centerOfMap);
	
	headNode->setPrev(tailNode);
	headNode->setNext(nullptr);
	tailNode->setNext(headNode);
	tailNode->setPrev(nullptr);
}

sf::Vector2u SnakeClass::getHeadLocation() {
	return headNode->getLocation();
}

int SnakeClass::move(MapClass &map, int dir) {
	int moveResult = CLEAR;
	map.updateScore(MOVE_PENALTY);

	sf::Vector2u headLocation = headNode->getLocation();
	map.changeBoxColor(headLocation, WHITE);

	if(dir == UP) headLocation.y--;
	else if (dir == DOWN) headLocation.y++;
	else if (dir == LEFT) headLocation.x--;
	else if (dir == RIGHT) headLocation.x++;

	SnakeBodyNodeClass *newHead = new SnakeBodyNodeClass;
	moveResult = map.changeBoxColor(headLocation, RED);
	newHead->setLocation(headLocation);

	SnakeBodyNodeClass *oldHead = headNode;
	headNode = newHead;
	newHead->setPrev(oldHead);
	oldHead->setNext(newHead);
	newHead->setNext(nullptr);

	if (moveResult == WHITE || map.getScore() <= 0) {
		map.updateScore(KILL_PENALTY);
		moveResult = GAME_OVER;
	}
	else if (moveResult == BLUE) {
		moveResult = EAT_FOOD;
		map.updateScore(FOOD_REWARD);
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

SnakeClass::~SnakeClass(){
	while (tailNode != nullptr) {
		SnakeBodyNodeClass *temp = tailNode->getNext();
		delete tailNode;
		tailNode = temp;
	}
}
