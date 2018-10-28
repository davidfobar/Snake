#include "SnakeGameClass.h"
#include <iostream>
using namespace std;

SnakeGameClass::SnakeGameClass() {}

void SnakeGameClass::getState(GameStateClass &s) {
	sf::Vector2u headLoc = snake->getHeadLocation();
	sf::Vector2u foodLoc = food.getLocation();

	int gameState[8] = {};

	s.posx = map.getNearestPosX(headLoc);
	s.posy = map.getNearestPosY(headLoc);
	s.negx = map.getNearestNegX(headLoc);
	s.negy = map.getNearestNegY(headLoc);

	if (foodLoc.x >= headLoc.x) s.fposx = uint8_t(foodLoc.x - headLoc.x);
	else s.fposx = 0;

	if (foodLoc.y >= headLoc.y) s.fposy = uint8_t(foodLoc.y - headLoc.y);
	else s.fposy = 0;

	if (foodLoc.x < headLoc.x) s.fnegx = uint8_t(headLoc.x - foodLoc.x);
	else s.fnegx = 0;

	if (foodLoc.y < headLoc.y) s.fnegy = uint8_t(headLoc.y - foodLoc.y);
	else s.fnegy = 0;

	s.score = map.getScore();
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

bool SnakeGameClass::moveSnake(int nextMove) {
	bool gameOver = false;
	int moveResult = snake->move(map, nextMove);

	if (moveResult == GAME_OVER) {
		gameOver = true;
	}
	else if (moveResult == EAT_FOOD) {
		food.createNew(map);
	}

	return gameOver;
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
