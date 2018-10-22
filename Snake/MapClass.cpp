#include "MapClass.h"

MapClass::MapClass() {
	mapTiles = NULL;
}

MapClass::MapClass(sf::Vector2u windowSize, bool random) : scoreBoard() {
	if(random)std::srand(std::time(0));
	mapTiles = NULL;
	numAcross = (windowSize.x / BOX_SIZE);
	numDown = ((windowSize.y - SCOREBOARD_HEIGHT) / BOX_SIZE);

	mapTiles = new BoxClass*[numDown];
	for (int i = 0; i < numDown; i++) {
		mapTiles[i] = new BoxClass[numAcross];
	}

	for (int i = 0; i < numDown; i++) {
		for (int j = 0; j < numAcross; j++) {
			sf::Vector2u loc(j*BOX_SIZE, i*BOX_SIZE + SCOREBOARD_HEIGHT);
			mapTiles[i][j] = BoxClass(loc, BLACK);
		}
	}

	setExteriorWalls();
}

MapClass::~MapClass() {
}

void MapClass::draw(sf::RenderWindow &window) {
	
	for (int i = 0; i < numDown; i++) {
		for (int j = 0; j < numAcross; j++) {
			mapTiles[i][j].draw(window);
		}
	}
	scoreBoard.draw(window);
}

void MapClass::setExteriorWalls() {
	for (int j = 0; j < numAcross; j++) {
		mapTiles[0][j].setColor(WHITE);
		mapTiles[numDown-1][j].setColor(WHITE);
	}
	for (int i = 0; i < numDown; i++) {
		mapTiles[i][0].setColor(WHITE);
		mapTiles[i][numAcross-1].setColor(WHITE);
	}
}

sf::Vector2u MapClass::getRandLocation(){
	sf::Vector2u randLoc;
	bool clearSpaceFound = false;
	int x;
	int y;

	while (!clearSpaceFound) {
		x = rand() % (numAcross);
		y = rand() % (numDown);

		if (mapTiles[x][y].isNotFilled()) clearSpaceFound = true;
	}
	randLoc.x = x;
	randLoc.y = y;

	return randLoc;
}

sf::Vector2u MapClass::getCenterLocation() {
	sf::Vector2u center(numDown/2, numAcross/2);
	return center;
}

int MapClass::changeBoxColor(sf::Vector2u location, int inColor){
	int prevColor = mapTiles[location.x][location.y].getColor();
	mapTiles[location.x][location.y].setColor(inColor);
	return prevColor;
}

void MapClass::updateScore() {
	scoreBoard.updateScore();
}