#include "BoxClass.h"
#include <iostream>
using namespace std;


BoxClass::BoxClass()  {
}

BoxClass::BoxClass(sf::Vector2u inLoc, int inColor) : thisBox(sf::Vector2f(BOX_SIZE, BOX_SIZE)) {
	location = inLoc;
	thisBox.setPosition(float(location.x), float(location.y));
	setColor(inColor);
}

void BoxClass::draw(sf::RenderWindow &window) {
	window.draw(thisBox);
}

void BoxClass::setColor(int inColor) {
	color = inColor;
	if (inColor == WHITE) thisBox.setFillColor(sf::Color::White);
	else if (inColor == BLACK) thisBox.setFillColor(sf::Color::Black);
	else if (inColor == BLUE) thisBox.setFillColor(sf::Color::Blue);
	else if (inColor == RED) thisBox.setFillColor(sf::Color::Red);
}

int BoxClass::getColor() {
	return color;
}

int BoxClass::getX() {
	return int(location.x);
}

int BoxClass::getY() {
	return int(location.y);
}

bool BoxClass::isNotFilled(){
	return (color == BLACK);
}