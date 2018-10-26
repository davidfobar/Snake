#include "SnakeGameClass.h"
#include <iostream>
using namespace std;

SnakeGameClass::SnakeGameClass() {}

int SnakeGameClass::getScore() {
	return map.getScore();
}

uint8_t* SnakeGameClass::getState() {
	sf::Vector2u headLoc = snake->getHeadLocation();
	sf::Vector2u foodLoc = food.getLocation();

	uint8_t gameState[8] = {};

	gameState[0] = map.getNearestPosX(headLoc);
	gameState[1] = map.getNearestPosY(headLoc);
	gameState[2] = map.getNearestNegX(headLoc);
	gameState[3] = map.getNearestNegY(headLoc);

	if (foodLoc.x > headLoc.x) gameState[4] = uint8_t(foodLoc.x - headLoc.x);
	else gameState[4] = 0;

	if (foodLoc.y > headLoc.y) gameState[5] = uint8_t(foodLoc.y - headLoc.y);
	else gameState[5] = 0;

	if (foodLoc.x < headLoc.x) gameState[6] = uint8_t(headLoc.x - foodLoc.x);
	else gameState[6] = 0;

	if (foodLoc.y < headLoc.y) gameState[7] = uint8_t(headLoc.y - foodLoc.y);
	else gameState[7] = 0;

	return gameState;
}

int SnakeGameClass::getMapWidth() {
	return map.getSize().x;
}

int SnakeGameClass::getMapHeight() {
	return map.getSize().y;
}

SnakeGameClass::SnakeGameClass(sf::RenderWindow &window) : 
	map(window.getSize(), ENABLE_RANDOM){
	snake = new SnakeClass(map);
	food.createNew(map);
}

void SnakeGameClass::moveSnake(int nextMove) {
	int moveResult = snake->move(map, nextMove);

	if (moveResult == GAME_OVER) {
		reset();
	}
	else if (moveResult == EAT_FOOD) {
		food.createNew(map);
	}
}

void SnakeGameClass::reset() {
	map.reset();
	delete snake;
	snake = new SnakeClass(map);
	food.createNew(map);
}

void SnakeGameClass::draw(sf::RenderWindow &window) {
	map.draw(window);
}

SnakeGameClass::~SnakeGameClass()
{
}
