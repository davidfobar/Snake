#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/system/Vector2.hpp>
#include <sstream>
#include <iostream>
#include "constants.h"

class ScoreBoardClass
{
private:
	int curScore;

public:
	ScoreBoardClass();
	~ScoreBoardClass();
	void updateScore(int val);
	void reset();
	void draw(sf::RenderWindow &window);
	int getScore();
};

