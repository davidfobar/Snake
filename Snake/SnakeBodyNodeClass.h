#pragma once
#include "BoxClass.h"

class SnakeBodyNodeClass : public BoxClass
{
private:

	sf::Vector2u location;
	SnakeBodyNodeClass *prevNode;
	SnakeBodyNodeClass *nextNode;

public:
	SnakeBodyNodeClass();
	~SnakeBodyNodeClass();
	sf::Vector2u getLocation();
	void setLocation(sf::Vector2u &inLocation);
	void setPrev(SnakeBodyNodeClass *inPrev);
	void setNext(SnakeBodyNodeClass *inNext);
	SnakeBodyNodeClass* getPrev();
	SnakeBodyNodeClass* getNext();
};

