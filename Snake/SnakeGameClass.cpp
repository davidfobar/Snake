#include "SnakeGameClass.h"

SnakeGameClass::SnakeGameClass() {}

int SnakeGameClass::getScore() {
	return map.getScore();
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
