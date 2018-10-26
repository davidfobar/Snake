#include "MapClass.h"
#include <iostream>
using namespace std;

MapClass::MapClass() {
	mapTiles = NULL;
}

int MapClass::getScore() {
	return scoreBoard.getScore();
}

MapClass::MapClass(sf::Vector2u windowSize, bool random) : scoreBoard() {
	if(random)std::srand(std::time(0));
	mapTiles = NULL;
	_x = (windowSize.x / BOX_SIZE);
	_y = ((windowSize.y - SCOREBOARD_HEIGHT) / BOX_SIZE);

	mapTiles = new BoxClass*[_x];
	for (int i = 0; i < _x; i++) {
		mapTiles[i] = new BoxClass[_y];
	}

	reset();
}

MapClass::~MapClass() {
}

void MapClass::reset() {
	for (int i = 0; i < _x; i++) {
		for (int j = 0; j < _y; j++) {
			sf::Vector2u loc(i*BOX_SIZE, j*BOX_SIZE + SCOREBOARD_HEIGHT);
			mapTiles[i][j] = BoxClass(loc, BLACK);
		}
	}

	setExteriorWalls();
	scoreBoard.reset();
}

void MapClass::draw(sf::RenderWindow &window) {
	
	for (int i = 0; i < _x; i++) {
		for (int j = 0; j < _y; j++) {
			mapTiles[i][j].draw(window);
		}
	}
	scoreBoard.draw(window);
}

void MapClass::setExteriorWalls() {
	for (int i = 0; i < _x; i++) {
		mapTiles[i][0].setColor(WHITE);
		mapTiles[i][_y-1].setColor(WHITE);
	}
	for (int i = 0; i < _y; i++) {
		mapTiles[0][i].setColor(WHITE);
		mapTiles[_x-1][i].setColor(WHITE);
	}
}

sf::Vector2u MapClass::getRandLocation(){
	sf::Vector2u randLoc;
	bool clearSpaceFound = false;
	int x;
	int y;

	while (!clearSpaceFound) {
		x = rand() % (_x-1) + 1;
		y = rand() % (_y-1) + 1;

		if (mapTiles[x][x].isNotFilled()) clearSpaceFound = true;
	}
	randLoc.x = x;
	randLoc.y = y;

	return randLoc;
}

sf::Vector2u MapClass::getCenterLocation() {
	sf::Vector2u center(_x/2, _y/2);
	return center;
}

int MapClass::changeBoxColor(sf::Vector2u location, int inColor){
	int prevColor = mapTiles[location.x][location.y].getColor();
	mapTiles[location.x][location.y].setColor(inColor);
	return prevColor;
}

void MapClass::updateScore(int val) {
	scoreBoard.updateScore(val);
}