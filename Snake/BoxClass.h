#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/system/Vector2.hpp>

const int BOX_SIZE = 50;
const int BLACK = 0;
const int WHITE = 1;
const int BLUE = 2;
const int RED = 3;

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

