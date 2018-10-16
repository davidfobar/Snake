#include "SnakeBodyNodeClass.h"



SnakeBodyNodeClass::SnakeBodyNodeClass(){
}

SnakeBodyNodeClass::~SnakeBodyNodeClass(){
}

sf::Vector2u SnakeBodyNodeClass::getLocation(){
	return location;
}

void SnakeBodyNodeClass::setLocation(sf::Vector2u &inLocation){
	location = inLocation;
}

void SnakeBodyNodeClass::setPrev(SnakeBodyNodeClass *inPrev){
	prevNode = inPrev;
}

void SnakeBodyNodeClass::setNext(SnakeBodyNodeClass *inNext){
	nextNode = inNext;
}

SnakeBodyNodeClass* SnakeBodyNodeClass::getPrev() {
	return prevNode;
}

SnakeBodyNodeClass* SnakeBodyNodeClass::getNext() {
	return nextNode;
}