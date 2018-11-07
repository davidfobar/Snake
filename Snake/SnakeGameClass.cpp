#include "SnakeGameClass.h"
#include <iostream>
using namespace std;

SnakeGameClass::SnakeGameClass() {}

GameStateClass SnakeGameClass::getState() {
	GameStateClass s;
	double foodHeadDist = sqrt((snake->getHeadLocation().x - food.getLocation().x)*(snake->getHeadLocation().x - food.getLocation().x)
		+ (snake->getHeadLocation().y - food.getLocation().y)*(snake->getHeadLocation().y - food.getLocation().y));
	s.updateState(map.getFullMapState(), map.getScore(), numMoves, foodHeadDist);
	return s;
}

int SnakeGameClass::getMapWidth() {
	return map.getSize().x;
}

int SnakeGameClass::getMapHeight() {
	return map.getSize().y;
}

SnakeGameClass::SnakeGameClass(sf::RenderWindow &window) : 	map(window.getSize()){
	reset();
}

bool SnakeGameClass::moveSnake(int nextMove) {
	bool gameOver = false;
	numMoves++;
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
	numMoves = 0;
}

void SnakeGameClass::draw(sf::RenderWindow &window) {
	map.draw(window);
}

SnakeGameClass::~SnakeGameClass()
{
}
