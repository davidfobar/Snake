#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/system/Vector2.hpp>
#include "constants.h"

class BoxClass
{
private:
	sf::Vector2u location;
	int color;
protected:
	sf::RectangleShape thisBox;
public:
	BoxClass();
	BoxClass(sf::Vector2u windowSize, int inColor);
	void draw(sf::RenderWindow &window);
	void setColor(int inColor);
	int getColor();
	int getX();
	int getY();
	bool isNotFilled();
};

