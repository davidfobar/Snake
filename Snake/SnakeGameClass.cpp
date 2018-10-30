#include "SnakeGameClass.h"
#include <iostream>
using namespace std;

SnakeGameClass::SnakeGameClass() {}

void SnakeGameClass::getState(GameStateClass &s) {
	s.updateState( map.getFullMapState(), map.getScore() );
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
